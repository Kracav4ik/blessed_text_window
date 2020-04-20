#include "HUD.h"

#include "GameScreen.h"
#include <curses.h>

void HUD::process(float elapsed) {
    _show_elapsed -= elapsed;
}

void HUD::render(const GameScreen& scr) const {
    if (_show_elapsed > 0) {
        mvaddch(0, 0, ' ');
        wprintw(stdscr, _text.c_str());
    }

    mvaddch(LINES - 1, 0, ' ');
    wprintw(stdscr, "HP %d ", scr.player_hp());
}

void HUD::set_text(const std::string& text, float seconds) {
    _text = text;
    _show_elapsed = seconds;
}
