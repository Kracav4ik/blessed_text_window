#include "InputManager.h"

#include "utils.hpp"

#include <curses.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <windows.h>
#include <wincon/pdcwin.h>
#endif

#include <utility>

void InputManager::init() {
    mouse_set(ALL_MOUSE_EVENTS);
}

#ifdef __EMSCRIPTEN__
extern "C" {

void EMSCRIPTEN_KEEPALIVE keydown_handler(const char* key) {
    InputManager::get().process_key(key[0], true);
}

void EMSCRIPTEN_KEEPALIVE keyup_handler(const char* key) {
    InputManager::get().process_key(key[0], false);
}

void EMSCRIPTEN_KEEPALIVE mouse_down_handler(bool left_pressed, bool right_pressed) {
    InputManager::get().set_mouse_button_state(left_pressed, right_pressed);
}

void EMSCRIPTEN_KEEPALIVE mouse_up_handler(bool left_pressed, bool right_pressed) {
    InputManager::get().set_mouse_button_state(left_pressed, right_pressed);
}


void EMSCRIPTEN_KEEPALIVE mouse_move_handler(float x, float y) {
    InputManager::get().set_mouse_pos((int)x, (int)y);
}

}
#endif

void InputManager::process_key(uint8_t key, bool pressed) {
    _key_pressed[key] = pressed;
    if (pressed && _key_states.count(key) != 0) {
        _key_states[key]();
    }
}

void InputManager::set_mouse_button_state(bool left_pressed, bool right_pressed) {
    _left_pressed = left_pressed;
    _right_pressed = right_pressed;
}

void InputManager::set_mouse_pos(int x, int y) {
    _mouse_pos = PointI(x, y);
}

void InputManager::check_input() {
#ifndef __EMSCRIPTEN__
    DWORD count;
    GetNumberOfConsoleInputEvents(pdc_con_in, &count);

    for (int i = 0; i < count; ++i) {
        DWORD unused;
        INPUT_RECORD ir;
        ReadConsoleInput(pdc_con_in, &ir, 1, &unused);

        if (ir.EventType == KEY_EVENT) {
            const auto& e = ir.Event.KeyEvent;
            process_key(e.wVirtualKeyCode, e.bKeyDown);
        } else if (ir.EventType == MOUSE_EVENT) {
            const auto& e = ir.Event.MouseEvent;
            set_mouse_pos(e.dwMousePosition.X, e.dwMousePosition.Y);
            set_mouse_button_state((e.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0, (e.dwButtonState & RIGHTMOST_BUTTON_PRESSED) != 0);
        }
    }
#endif
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
