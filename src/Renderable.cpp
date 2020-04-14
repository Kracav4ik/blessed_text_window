#include "Renderable.h"
#include "RenderManager.h"
#include "Screen.h"
#include "ObjectManager.hpp"

Renderable::Renderable(Screen& screen): _screen(screen) {
    _screen.add_renderable(this);
}

Renderable::~Renderable() {
    _screen.remove_renderable(this);
}

bool Renderable::is_danger_theme() const {
    return RenderManager::get().is_danger_theme();
}
