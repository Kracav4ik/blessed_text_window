#include "RenderManager.h"
#include <curses.h>

void RenderManager::render() {
    for (const auto& renderable : _objects) {
        renderable->render();
    }
}

void RenderManager::init() {
    // background character
    char bg = '.';

    // init
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    bkgd(bg);
}
