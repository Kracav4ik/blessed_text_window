#pragma once

#include "Singleton.h"

class RenderManager : public Singleton<RenderManager> {
SINGLETON_CTOR(RenderManager)
public:
    void init();
    void render() const;
    void restore();
    void danger();

    bool is_danger_theme() const;

private:
    bool _is_danger_theme = false;
};
