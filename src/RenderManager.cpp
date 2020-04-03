#include "RenderManager.h"
#include <curses.h>

void RenderManager::render() {
    clear();
    for (const auto& renderable : get_objects()) {
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

    init_pair(100, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(101, COLOR_BLUE, COLOR_BLACK); // enemies default
    init_pair(102, COLOR_CYAN, COLOR_BLACK); // missiles default

    init_pair(200, COLOR_BLACK, COLOR_RED); // danger theme
    init_pair(201, COLOR_BLUE, COLOR_RED); // enemies danger
    init_pair(202, COLOR_CYAN, COLOR_RED); // missiles danger
    restore();
}

void RenderManager::restore() {
    bkgd(COLOR_PAIR(100) | bg_sing);
    _is_danger_theme = false;
}

void RenderManager::danger() {
    bkgd(COLOR_PAIR(200) | bg_sing);
    _is_danger_theme = true;
}

bool RenderManager::is_danger_theme() const {
    return _is_danger_theme;
}

void RenderManager::clear() {
    for (int x = 0; x < COLS; ++x) {
        for (int y = 0; y < LINES; ++y) {
            mvaddch(y, x, bg_sing);
        }
    }
}
