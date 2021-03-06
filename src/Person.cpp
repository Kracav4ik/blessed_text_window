#include "Person.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "GameScreen.h"
#include "utils.hpp"

#include <curses.h>

static const float SHOT_DELAY = 0.3;

void Person::process(float elapsed) {
    _was_damaged = false;

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
    set_velocity(PointF(x_vel, y_vel).norm() * vel_val);

    GameObject::process(elapsed);

    _shot_elapsed += elapsed;
    if (InputManager::get().is_left_pressed() && _shot_elapsed >= SHOT_DELAY) {
        auto target = InputManager::get().mouse_pos();
        if (target != grid_pos()) {
            _game.launch_missile(target);
            _shot_elapsed = 0;
        }
    }
}

void Person::render() const {
    auto theme = COLOR_PAIR(103);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(203);
    }
    mvaddch(grid_round(pos().y()), grid_round(pos().x()), '@' | theme);
}

void Person::take_damage(int damage) {
    _health_points -= damage;
    _was_damaged = true;
}

void Person::heal(int value) {
    _health_points += value;
}

bool Person::was_damaged() const {
    return _was_damaged;
}

int Person::health_points() const {
    return _health_points;
}

Person::Person(GameScreen& game_screen) : GameObject(game_screen), Renderable(game_screen) {
    add_flags(PLAYER_FLAG);
}

bool Person::is_alive() const {
    return _health_points > 0;
}

float Person::vision_value() {
    return _vision_value;
}
