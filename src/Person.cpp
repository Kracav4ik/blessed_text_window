#include "Person.h"

#include "InputManager.h"
#include "GameManager.h"

#include <curses.h>
#include <cmath>

void Person::process(float elapsed) {
    mvaddch(0, 100, '>');
    wprintw(stdscr, "                                                                                                      ");
    mvaddch(0, 100, '>');
    wprintw(stdscr, "elapsed %f spd %f %f pos %f %f", elapsed, _velocity.x(), _velocity.y(), _pos.x(), _pos.y());

    mvaddch(1, 100, '>');
    wprintw(stdscr, "                                                                                                      ");
    mvaddch(1, 100, '>');
    float vel_val = 18;
    int x_vel = 0;
    int y_vel = 0;
    if (InputManager::get().is_key_pressed('W')) {
        wprintw(stdscr, "W");
        y_vel -= vel_val;
    }
    if (InputManager::get().is_key_pressed('S')) {
        wprintw(stdscr, "S");
        y_vel += vel_val;
    }
    if (InputManager::get().is_key_pressed('A')) {
        wprintw(stdscr, "A");
        x_vel -= vel_val;
    }
    if (InputManager::get().is_key_pressed('D')) {
        wprintw(stdscr, "D");
        x_vel += vel_val;
    }
    _velocity.set_x(x_vel);
    _velocity.set_y(y_vel);

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

void Person::render() {
    mvaddch(grid_round(_old_pos.y()), grid_round(_old_pos.x()), '.'); // TODO: fix
    mvaddch(grid_round(pos().y()), grid_round(pos().x()), '@');
}
