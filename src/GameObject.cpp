#include "GameObject.h"

#include "GameManager.h"
#include "ObjectManager.hpp"

#include <cmath>
#include <curses.h>

GameObject::GameObject() {
    init();
}

GameObject::GameObject(const Point& pos): _pos(pos), _velocity() {
    init();
}

const Point& GameObject::pos() const {
    return _pos;
}

Point& GameObject::pos() {
    return _pos;
}

void GameObject::set_pos(const Point& pos) {
    _pos = pos;
}

const Point& GameObject::velocity() const {
    return _velocity;
}

Point& GameObject::velocity() {
    return _velocity;
}

void GameObject::set_velocity(const Point& velocity) {
    _velocity = velocity;
}

GameObject::~GameObject() {
    GameManager::get().remove_object(this);
}

void GameObject::init() {
    GameManager::get().add_object(this);
}

void GameObject::fix_pos() {
    _pos.set_x((grid_round(_pos.x()) + COLS) % COLS);
    _pos.set_y((grid_round(_pos.y()) + LINES) % LINES);
}

