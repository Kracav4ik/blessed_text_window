#include "Missile.h"

#include "GameManager.h"
#include "utils.hpp"

#include <curses.h>

void Missile::process(float elapsed) {
    auto new_pos = pos() + elapsed * velocity();
    auto new_grid_pos = grid_round(new_pos);

    bool collided = !GameManager::get().can_pass(new_grid_pos);
    set_pos(new_pos);
    if (collided) {
        GameManager::get().kill(*this, new_grid_pos);
    }
}

void Missile::render() {
    auto theme = COLOR_PAIR(102);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(202);
    }
    mvaddch(grid_pos().y(), grid_pos().x(), '*' | theme);
}

void Missile::direct_velocity(const PointF& direction) {
    _velocity = direction.norm() * 50.f;
}
