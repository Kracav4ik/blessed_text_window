#include <iostream>
#include <curses.h>
#include <windows.h>
#include <wincon/pdcwin.h>



bool KEY_STATE[256] = {false};
int MOUSE_X = 0;
int MOUSE_Y = 0;
DWORD MOUSE_STATE;


void check_input() {
    DWORD count;
    GetNumberOfConsoleInputEvents(pdc_con_in, &count);

    for (int i = 0; i < count; ++i) {
        DWORD unused;
        INPUT_RECORD ir;
        ReadConsoleInput(pdc_con_in, &ir, 1, &unused);

        if (ir.EventType == KEY_EVENT) {
            const auto& e = ir.Event.KeyEvent;
            KEY_STATE[e.wVirtualKeyCode] = e.bKeyDown;
        } else if (ir.EventType == MOUSE_EVENT) {
            const auto& e = ir.Event.MouseEvent;
            MOUSE_X = e.dwMousePosition.X;
            MOUSE_Y = e.dwMousePosition.Y;
            MOUSE_STATE = e.dwButtonState;
        }
    }
}

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
    bkgd(bg);


    while (true) {
        mvaddch(person_y, person_x, '@');
        auto move = [person_y, person_x, bg](int val, bool make_less, int clip) {
//            mvaddch(person_y, person_x, bg);
            if (make_less) {
                return (val + clip - 1) % clip;
            }
            return (val + 1) % clip;
        };

        check_input();

        if ((MOUSE_STATE & FROM_LEFT_1ST_BUTTON_PRESSED) != 0) {
            mvaddch(MOUSE_Y, MOUSE_X, '*');
            wprintw(stdscr, "Position: Y: %d X: %d", MOUSE_Y, MOUSE_X);
        }

        // exit
        if (KEY_STATE['q'] || KEY_STATE['Q'] ) {
            curs_set(1);
            endwin();
            return EXIT_SUCCESS;
        }

        // moves
        // up
        if (KEY_STATE['w'] || KEY_STATE['W'] ) {
            person_y = move(person_y, true, LINES);
        }
        // left
        if (KEY_STATE['a'] || KEY_STATE['A'] ) {

            person_x = move(person_x, true, COLS);
        }
        // down
        if (KEY_STATE['s'] || KEY_STATE['S'] ) {

            person_y = move(person_y, false, LINES);
        }
        // right
        if (KEY_STATE['d'] || KEY_STATE['D'] ) {
            person_x = move(person_x, false, COLS);
        }
        getch();
        napms(50);
    }
}
