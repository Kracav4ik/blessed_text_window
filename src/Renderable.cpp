#include "Renderable.h"
#include "RenderManager.h"
#include "ObjectManager.hpp"

Renderable::Renderable() {
    RenderManager::get().add_object(this);
}

Renderable::~Renderable() {
    RenderManager::get().remove_object(this);
}
