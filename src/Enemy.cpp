#include "Enemy.h"

#include "GameScreen.h"
#include "utils.hpp"

#include <curses.h>

static const float HIT_DELAY = 0.5;

void Enemy::process(float elapsed) {
    _hit_elapsed += elapsed;
    if (!can_act()) {
        return;
    }
    float vel_val = 10;
    set_velocity((PointF(_game.player_pos()) - pos()).norm() * vel_val);

    GameObject::process(elapsed);

    int distance = dist2(_game.player_pos(), grid_pos());
    if (distance < 3) {
        _hit_elapsed = 0;
        _game.damage_player(damage());
    }
}

void Enemy::render() const {
    if (!_visible) {
        return;
    }
    auto theme = COLOR_PAIR(101);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(201);
    }
    mvaddch(grid_pos().y(), grid_pos().x(), _type | theme);
}

int Enemy::damage() const {
    return _damage;
}

int Enemy::health_points() const {
    return _health_points;
}

bool Enemy::can_act() const {
    return _hit_elapsed > HIT_DELAY;
}

void Enemy::take_damage(int damage) {
    _health_points -= damage;
}

Enemy::Enemy(GameScreen& game_screen, int damage, int hp, char type)
    : GameObject(game_screen), Renderable(game_screen), _damage(damage), _health_points(hp), _type(type)
{
    add_flags(ENEMY_FLAG);
}
