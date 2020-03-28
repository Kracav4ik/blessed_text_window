#include "Person.h"

#include "InputManager.h"
#include "utils.hpp"

#include <curses.h>

void Person::process(float elapsed) {
    float vel_val = 18;
    float x_vel = 0;
    float y_vel = 0;
    if (InputManager::get().is_key_pressed('W')) {
        y_vel -= 1;
    }
    if (InputManager::get().is_key_pressed('S')) {
        y_vel += 1;
    }
    if (InputManager::get().is_key_pressed('A')) {
        x_vel -= 1;
    }
    if (InputManager::get().is_key_pressed('D')) {
        x_vel += 1;
    }
    _velocity = PointF(x_vel, y_vel).norm() * vel_val;

    GameObject::process(elapsed);
}

void Person::render() {
    mvaddch(grid_round(_old_grid_pos.y()), grid_round(_old_grid_pos.x()), '.'); // TODO: fix
    mvaddch(grid_round(pos().y()), grid_round(pos().x()), '@');
}
