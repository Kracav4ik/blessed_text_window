#include "RenderManager.h"
#include "ScreenManager.h"
#include <curses.h>

#define COLOR_BRIGHT   8

void RenderManager::render() const {
    for (int x = 0; x < COLS; ++x) {
        for (int y = 0; y < LINES; ++y) {
            mvaddch(y, x, ' ');
        }
    }
    ScreenManager::get().render();
    wrefresh(stdscr);
}

void RenderManager::init() {
    // init
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    start_color();

    init_pair(10, COLOR_CYAN, COLOR_BLACK); // text

    init_pair(100, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(101, COLOR_GREEN, COLOR_BLACK); // enemies default
    init_pair(102, COLOR_BRIGHT | COLOR_YELLOW, COLOR_BLACK); // missiles default
    init_pair(103, COLOR_BRIGHT | COLOR_WHITE, COLOR_BLACK); // player default
    init_pair(104, COLOR_BRIGHT | COLOR_RED, COLOR_BRIGHT | COLOR_WHITE); // item default

    init_pair(200, COLOR_BLACK, COLOR_RED); // danger theme
    init_pair(201, COLOR_GREEN, COLOR_RED); // enemies danger
    init_pair(202, COLOR_BRIGHT | COLOR_YELLOW, COLOR_RED); // missiles danger
    init_pair(203, COLOR_BRIGHT | COLOR_WHITE, COLOR_RED); // player danger
    init_pair(204, COLOR_BRIGHT | COLOR_RED, COLOR_RED); // item danger
    restore();
}

void RenderManager::restore() {
    bkgd(COLOR_PAIR(100));
    _is_danger_theme = false;
}

void RenderManager::danger() {
    bkgd(COLOR_PAIR(200));
    _is_danger_theme = true;
}

bool RenderManager::is_danger_theme() const {
    return _is_danger_theme;
}
