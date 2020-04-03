#pragma once

#include "Renderable.h"
#include "Singleton.h"
#include "ObjectManager.h"

class RenderManager : public Singleton<RenderManager>, public ObjectManager<Renderable> {
SINGLETON_CTOR(RenderManager)
public:
    void init();
    void render();
    void restore();
    void danger();

    bool is_danger_theme() const;

private:
    // background character
    char bg_sing = '.';
    void clear();

    bool _is_danger_theme = false;
};
