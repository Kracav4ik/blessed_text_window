#include "Enemy.h"
#include "GameManager.h"

#include <curses.h>

void Enemy::process(float elapsed) {
    Point ppos = GameManager::get().player_pos();
    float vel_val = 10;
    if (ppos.y() < pos().y()) {
        _velocity.set_y(-vel_val);
    } else if (ppos.y() > pos().y()) {
        _velocity.set_y(vel_val);
    }
    if (ppos.x() < pos().x()) {
        _velocity.set_x(-vel_val);
    } else if (ppos.x() > pos().x()) {
        _velocity.set_x(vel_val);
    }
    const Point& new_pos = _pos + elapsed * _velocity;

    if (GameManager::get().can_pass(new_pos)) {
        _old_pos = _pos;
        _pos += elapsed * _velocity;
    } else {
        _velocity.set_x(0);
        _velocity.set_y(0);
    }
    fix_pos();
}

void Enemy::render() {
    mvaddch(grid_round(_old_pos.y()), grid_round(_old_pos.x()), '.'); // TODO: fix
    mvaddch(grid_round(pos().y()), grid_round(pos().x()), 'g' | COLOR_PAIR(2));
}
