#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "Person.h"
#include "Enemy.h"
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
    for (const auto& object : _objects) {
        int distance = dist2(_person->grid_pos(), object->grid_pos());
        if (distance != 0 && distance < min_distance) {
            min_distance = distance;
        }
        object->process(elapsed);
    }
    if (min_distance < 10) {
        RenderManager::get().danger();
    } else {
        RenderManager::get().restore();
    }
}

PointI GameManager::player_pos() {
    return _person->grid_pos();
}

bool GameManager::can_pass(const PointI& p) const {
    for (const auto& object : _objects) {
        int distance = dist2(p, object->grid_pos());
        if (distance == 0 || p.x() < 0 || p.y() < 0 || p.x() >= COLS || p.y() >= LINES) {
            return false;
        }
    }

    return true;
}

void GameManager::generate_enemy() {
    _enemies.push_back(std::make_unique<Enemy>());
    _enemies.back()->set_grid_pos(PointI(rand() % COLS, rand() % LINES));
}
