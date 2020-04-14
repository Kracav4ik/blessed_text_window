#include "Enemy.h"

#include "GameScreen.h"
#include "utils.hpp"

#include <curses.h>

void Enemy::process(float elapsed) {
    float vel_val = 10;
    set_velocity((PointF(_game.player_pos()) - pos()).norm() * vel_val);

    GameObject::process(elapsed);
}

void Enemy::render() const {
    auto theme = COLOR_PAIR(101);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(201);
    }
    mvaddch(grid_pos().y(), grid_pos().x(), _type | theme);
}

float Enemy::damage() const {
    return _damage;
}

Enemy::Enemy(GameScreen& game_screen, float damage, char type) : GameObject(game_screen), Renderable(game_screen), _damage(damage), _type(type) {}
