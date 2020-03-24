#include "GameObject.h"

#include "GameManager.h"
#include "ObjectManager.hpp"

GameObject::GameObject() {
    GameManager::get().add_object(this);
}

GameObject::~GameObject() {
    GameManager::get().remove_object(this);
}
