#include <iostream>
#include <curses.h>

int main() {
    // person coords
    int person_x = 0;
    int person_y = 0;

    // background character
    char bg = '.';

    // init
    initscr();
    noecho();
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
    mouse_set(ALL_MOUSE_EVENTS);
    bkgd(bg);


    while (true) {
        mvaddch(person_y, person_x, '@');
        auto move = [person_y, person_x, bg](int val, bool make_less, int clip) {
            mvaddch(person_y, person_x, bg);
            if (make_less) {
                return (val + clip - 1) % clip;
            }
            return (val + 1) % clip;
        };

        switch (getch()) {
            case 'q': // exit
            case 'Q':
                curs_set(1);
                endwin();
                return EXIT_SUCCESS;
            case KEY_MOUSE:
                request_mouse_pos();
                mvaddch(MOUSE_Y_POS, MOUSE_X_POS, '*');
                wprintw(stdscr, "Position: Y: %d X: %d", MOUSE_Y_POS, MOUSE_X_POS);
                break;
            // moves
            case 'w': // up
            case 'W':
                person_y = move(person_y, true, LINES);
                break;
            case 'a': // left
            case 'A':
                person_x = move(person_x, true, COLS);
                break;
            case 's': // down
            case 'S':
                person_y = move(person_y, false, LINES);
                break;
            case 'd': // right
            case 'D':
                person_x = move(person_x, false, COLS);
                break;
        }
        napms(50);
    }
}
