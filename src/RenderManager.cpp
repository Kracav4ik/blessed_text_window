#include "RenderManager.h"
#include <curses.h>

void RenderManager::render() {
    for (const auto& renderable : _objects) {
        renderable->render();
    }
    wrefresh(stdscr);
}

void RenderManager::init() {
    // init
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(2, COLOR_BLUE, COLOR_BLACK); // enemy
    init_pair(3, COLOR_BLACK, COLOR_RED); // danger
    restore();
}

void RenderManager::danger() {
    bkgd(COLOR_PAIR(3) | bg);
}

void RenderManager::restore() {
    bkgd(COLOR_PAIR(1) | bg);
}
