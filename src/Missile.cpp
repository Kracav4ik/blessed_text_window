#include "Missile.h"

#include "GameScreen.h"
#include "Person.h"
#include "utils.hpp"

#include <curses.h>
#include <cmath>

static const float MISSILE_SPEED = 70;

std::vector<PointI> generate_deltas(PointF from, PointF to);

void Missile::process(float elapsed) {
    auto new_pos = pos() + elapsed * velocity();

    auto check_pos = grid_pos();
    auto deltas = generate_deltas(pos(), new_pos);
    int count = 0;
    for (PointI delta : deltas) {
        check_pos += delta;
        count += 1;
        if (check_pos == _game.player_pos()) {
            continue;  // TODO: use game object tags to check collision with
        }
        bool collided = !_game.can_pass(check_pos, {this});
        if (collided) {
            _game.kill(*this, check_pos);
            new_pos = pos() + elapsed * count / deltas.size() * velocity();
            break;
        }
    }

    set_pos(new_pos);
    processed = true;
}

std::vector<PointI> generate_deltas(PointF from, PointF to) {
    PointI from_i = grid_round(from);
    PointI to_i = grid_round(to);
    PointI delta_i = to_i - from_i;
    int steps = std::max(std::abs(delta_i.x()), std::abs(delta_i.y()));

    std::vector<PointI> result;
    PointI prev_point = from_i;
    PointF start{from_i};
    PointF step = PointF{delta_i} / steps;
    for (int i = 0; i < steps; ++i) {
        PointI next_point = grid_round(start + (i + 1)*step);
        result.push_back(next_point - prev_point);
        prev_point = next_point;
    }
    return result;
}

template<typename T>
char display_delta(Point<T> delta) {
    if (delta.is_zero()) {
        return '*';
    }
    auto angle = atan2(-delta.y(), delta.x());
    if (angle < 0) {
        angle += M_PI;
    }
    if (M_PI/8 <= angle && angle < 3*M_PI/8) {
        return '/';
    }
    if (3*M_PI/8 <= angle && angle < 5*M_PI/8) {
        return '|';
    }
    if (5*M_PI/8 <= angle && angle < 7*M_PI/8) {
        return '\\';
    }
    return '-';
}

void Missile::render() const {
    auto theme = COLOR_PAIR(102);
    if (is_danger_theme()) {
        theme = COLOR_PAIR(202);
    }
    PointI draw_pos = grid_round(_old_pos);
    if (processed && draw_pos != grid_pos()) {
        for (PointI delta : generate_deltas(_old_pos, pos())) {
            draw_pos += delta;
            mvaddch(draw_pos.y(), draw_pos.x(), display_delta(delta) | theme);
        }
    } else {
        mvaddch(grid_pos().y(), grid_pos().x(), display_delta(velocity()) | theme);
    }
}

void Missile::direct_velocity(const PointF& direction) {
    set_velocity(direction.norm() * MISSILE_SPEED);
}

void Missile::set_pos(const PointF& new_pos) {
    if (_old_pos != pos()) {
        _old_pos = pos();
    }
    GameObject::set_pos(new_pos);
}

void Missile::set_grid_pos(const PointI& new_pos) {
    if (_old_pos != pos()) {
        _old_pos = pos();
    }
    GameObject::set_grid_pos(new_pos);
}

Missile::Missile(GameScreen& game_screen) : GameObject(game_screen), Renderable(game_screen) {}
