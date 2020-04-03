#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "Person.h"
#include "Enemy.h"
#include "Missile.h"
#include "utils.hpp"

#include <cmath>
#include <chrono>
#include <curses.h>

using namespace std::chrono;

GameManager::GameManager() = default;
GameManager::~GameManager() = default;

void GameManager::init() {
    _person = std::make_unique<Person>();

    InputManager::get().add_action('Q', [this]() {
        _running = false;
    });

    _now = system_clock::now();
    _running = true;
}

bool GameManager::running() {
    return _running;
}

void GameManager::process() {
    auto now = system_clock::now();
    float elapsed = duration_cast<microseconds>(now - _now).count() * 1.e-6f;
    _now = now;
    if (rand() % 10 > 8) {
        generate_enemy();
    }
    int min_distance = 10;
    for (const auto& object : get_objects()) {
        object->process(elapsed);
    }

    for (const auto& enemy : _enemies) {
        int distance = dist2(_person->grid_pos(), enemy->grid_pos());
        if (distance < min_distance) {
            min_distance = distance;
        }
    }

    if (min_distance < 10) {
        RenderManager::get().danger();
    } else {
        RenderManager::get().restore();
    }
}

void GameManager::delete_later(std::unique_ptr<GameObject>&& object) {
    _to_delete.push_back(std::move(object));
}

void GameManager::delete_objects() {
    std::vector<std::unique_ptr<GameObject>> to_delete;
    std::swap(to_delete, _to_delete);
}

PointI GameManager::player_pos() {
    return _person->grid_pos();
}

bool GameManager::can_pass(const PointI& p) const {
    for (const auto& object : get_objects()) {
        int distance = dist2(p, object->grid_pos());
        if (distance == 0 || p.x() < 0 || p.y() < 0 || p.x() >= COLS || p.y() >= LINES) {
            return false;
        }
    }

    return true;
}

void GameManager::kill(const Missile& missile, const PointI& target) {
    for (auto e_it = _enemies.begin(); e_it != _enemies.end(); ++e_it) {
        if (e_it->get()->grid_pos() == target) {
            auto enemy_ptr = std::move(*e_it);
            _enemies.erase(e_it);
            delete_later(std::move(enemy_ptr));
            break;
        }
    }

    for (auto m_it = _missiles.begin(); m_it != _missiles.end(); ++m_it) {
        if (m_it->get() == &missile) {
            auto missile_ptr = std::move(*m_it);
            _missiles.erase(m_it);
            delete_later(std::move(missile_ptr));
            break;
        }
    }
}

void GameManager::launch_missile(const PointI& target) {
    _missiles.push_back(std::make_unique<Missile>());
    _missiles.back()->set_grid_pos(_person->grid_pos());
    _missiles.back()->direct_velocity(PointF(target - _person->grid_pos()));
}

void GameManager::generate_enemy() {
    _enemies.push_back(std::make_unique<Enemy>());
    _enemies.back()->set_grid_pos(PointI(rand() % COLS, rand() % LINES));
}
