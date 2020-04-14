#include "Person.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "GameScreen.h"
#include "utils.hpp"

#include <curses.h>

static const float SHOT_DELAY = 0.3;

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
    set_velocity(PointF(x_vel, y_vel).norm() * vel_val);

    _shot_elapsed += elapsed;
    if (InputManager::get().is_left_pressed() && _shot_elapsed >= SHOT_DELAY) {
        _game.launch_missile(InputManager::get().mouse_pos());
        _shot_elapsed = 0;
    }

    GameObject::process(elapsed);
}

void Person::render() const {
    auto theme = COLOR_PAIR(100);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(200);
    }
    mvaddch(grid_round(pos().y()), grid_round(pos().x()), '@' | theme);
    RenderManager::get().display_hp((int)_heal_points);
}

void Person::take_damage(float damage) {
    _heal_points -= damage;
}

Person::Person(GameScreen& game_screen) : GameObject(game_screen), Renderable(game_screen) {}

bool Person::is_alive() const {
    return _heal_points > 0;
}
