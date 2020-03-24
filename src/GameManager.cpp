#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "Enemy.h"

#include <cmath>
#include <chrono>

using namespace std::chrono;

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
        int distance = grid_round(dist2(_person->pos(), object->pos()));
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

Point GameManager::player_pos() {
    return _person->pos();
}

bool GameManager::can_pass(const Point& p) const {
    for (const auto& object : _objects) {
        int distance = grid_round(dist2(p, object->pos()));
        if (distance == 0) {
            return false;
        }
    }

    return true;
}

void GameManager::generate_enemy() {
    auto* enemy = new Enemy;
    enemy->set_pos(Point::random());
    enemy->fix_pos();
    while (can_pass(enemy->pos())) {
        enemy->set_pos(Point::random());
        enemy->fix_pos();
    }
}
