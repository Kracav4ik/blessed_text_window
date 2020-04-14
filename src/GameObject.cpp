#include "GameObject.h"

#include "GameScreen.h"
#include "ObjectManager.hpp"
#include "utils.hpp"

GameObject::GameObject(GameScreen& game) : _game(game) {
    install();
}

GameObject::GameObject(const PointI& grid_pos, GameScreen& game): _pos(grid_pos), _grid_pos(grid_pos), _game(game) {
    install();
}

const PointF& GameObject::pos() const {
    return _pos;
}

void GameObject::set_pos(const PointF& pos) {
    _grid_pos = grid_round(pos);
    _pos = pos;
}

const PointI& GameObject::grid_pos() const {
    return _grid_pos;
}

void GameObject::set_grid_pos(const PointI& pos) {
    _grid_pos = pos;
    _pos = PointF(pos.x(), pos.y());
}

const PointF& GameObject::velocity() const {
    return _velocity;
}

void GameObject::set_velocity(const PointF& velocity) {
    _velocity = velocity;
}

GameObject::~GameObject() {
    _game.remove_game_object(this);
}

void GameObject::install() {
    _game.add_game_object(this);
}

void GameObject::process(float elapsed) {
    auto new_pos = pos() + elapsed * velocity();
    auto new_grid_pos = grid_round(new_pos);

    if (new_grid_pos != grid_pos() && !_game.can_pass(new_grid_pos)) {
        return;
    }
    set_pos(new_pos);
}

