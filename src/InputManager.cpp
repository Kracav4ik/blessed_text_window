#include "InputManager.h"

#include "utils.hpp"

#include <curses.h>
#include <windows.h>
#include <wincon/pdcwin.h>

#include <utility>

void InputManager::init() {
    mouse_set(ALL_MOUSE_EVENTS);
}

void InputManager::check_input() {
    DWORD count;
    GetNumberOfConsoleInputEvents(pdc_con_in, &count);

    for (int i = 0; i < count; ++i) {
        DWORD unused;
        INPUT_RECORD ir;
        ReadConsoleInput(pdc_con_in, &ir, 1, &unused);

        if (ir.EventType == KEY_EVENT) {
            const auto& e = ir.Event.KeyEvent;
            _key_pressed[e.wVirtualKeyCode] = e.bKeyDown;
            if (e.bKeyDown && _key_states.count(e.wVirtualKeyCode) != 0) {
                _key_states[e.wVirtualKeyCode]();
            }
        } else if (ir.EventType == MOUSE_EVENT) {
            const auto& e = ir.Event.MouseEvent;
            _mouse_pos = PointI(e.dwMousePosition.X, e.dwMousePosition.Y);

            _left_pressed = false;
            _right_pressed = false;
            if ((e.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0) {
                _left_pressed = true;
            }
            if ((e.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0) {
                _right_pressed = true;
            }
        }
    }
}

void InputManager::add_action(char key, std::function<void()> f) {
    _key_states[key] = std::move(f);
}

PointI InputManager::mouse_pos() const {
    return _mouse_pos;
}

bool InputManager::is_left_pressed() const {
    return _left_pressed;
}

bool InputManager::is_right_pressed() const {
    return _right_pressed;
}

bool InputManager::is_key_pressed(char key) const {
    return _key_pressed[key];
}
