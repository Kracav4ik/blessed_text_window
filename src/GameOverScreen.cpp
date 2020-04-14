#include "GameOverScreen.h"

#include "InputManager.h"
#include "ScreenManager.h"

#include <curses.h>

void GameOverScreen::process(float elapsed) {
    if (InputManager::get().is_key_pressed('R')) {
        ScreenManager::get().restart();
    }
}

void GameOverScreen::render() const {
    char border_sign = '#';
    auto theme = COLOR_PAIR(10);
    for (int x = left(); x < right(); ++x) {
        for (int y = top(); y < bottom(); ++y) {
            if (x == left() || x == right() - 1 || y == top() || y == bottom() - 1) {
                mvaddch(y, x, border_sign | theme);
            } else {
                mvaddch(y, x, _bg_sing | theme);
            }
        }
    }

    int offset = 10;
    mvaddch(top() + height() / 2 - 1, left() + offset, 'R' | theme);
    wprintw(stdscr, "estart or");
    mvaddch(top() + height() / 2, left() + offset, 'Q' | theme);
    wprintw(stdscr, "uit");
}

GameOverScreen::GameOverScreen(const PointI& pos, const PointI& size) : Screen(pos, size, ' ') {}
