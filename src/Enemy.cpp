#include "Enemy.h"
#include "GameManager.h"
#include "utils.hpp"

#include <curses.h>

void Enemy::process(float elapsed) {
    PointF player_pos{GameManager::get().player_pos()};
    float vel_val = 10;
    _velocity = (player_pos - pos()).norm() * vel_val;

    GameObject::process(elapsed);
}

void Enemy::render() {
    auto theme = COLOR_PAIR(101);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(201);
    }
    mvaddch(grid_pos().y(), grid_pos().x(), 'g' | theme);
}
