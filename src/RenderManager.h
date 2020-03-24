#pragma once

#include "Renderable.h"
#include "Singleton.h"
#include "ObjectManager.h"

class RenderManager : public Singleton<RenderManager>, public ObjectManager<Renderable> {
SINGLETON_CTOR(RenderManager)
public:
    void init();
    void render();
};
