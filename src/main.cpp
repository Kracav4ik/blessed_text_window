#include <iostream>
#include <curses.h>

int main() {
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
    mouse_set(ALL_MOUSE_EVENTS);

    std::string text = "Press q key to exit.";
    while (true) {
        mvaddstr(LINES / 2, (COLS - text.size()) / 2, text.c_str());

        switch (getch()) {
            case 'q':
            case 'Q':
                curs_set(1);
                endwin();
                return EXIT_SUCCESS;
            case KEY_MOUSE:
                request_mouse_pos();
                mvaddch(MOUSE_Y_POS, MOUSE_X_POS, '*');
                wprintw(stdscr, "Position: Y: %d X: %d", MOUSE_Y_POS, MOUSE_X_POS);
                break;
        }
        napms(50);
    }
}
