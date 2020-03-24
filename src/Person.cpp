#include "Person.h"

#include "InputManager.h"

#include <curses.h>

void Person::process(float elapsed) {
    float vel_val = 18;
    if (InputManager::get().is_key_pressed('W')) {
        _velocity.set_y(-vel_val);
    } else if (InputManager::get().is_key_pressed('S')) {
        _velocity.set_y(vel_val);
    } else {
        _velocity.set_y(0);
    }
    if (InputManager::get().is_key_pressed('A')) {
        _velocity.set_x(-vel_val);
    } else if (InputManager::get().is_key_pressed('D')) {
        _velocity.set_x(vel_val);
    } else {
        _velocity.set_x(0);
    }
    _pos += elapsed * _velocity;
}

const Point& Person::pos() const {
    return _pos;
}

Point& Person::pos() {
    return _pos;
}

void Person::set_pos(const Point& pos) {
    _pos = pos;
}

const Point& Person::velocity() const {
    return _velocity;
}

Point& Person::velocity() {
    return _velocity;
}

void Person::set_velocity(const Point& velocity) {
    _velocity = velocity;
}

void Person::render() {
    mvaddch(pos().y(), pos().x(), '@');
}
