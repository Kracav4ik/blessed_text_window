#pragma once

#include "Singleton.h"
#include "utils.h"

#include <unordered_map>
#include <functional>

class InputManager : public Singleton<InputManager> {
SINGLETON_CTOR(InputManager)
public:
    void init();
    void check_input();

    void add_action(char key, std::function<void()> f);
    PointI mouse_pos() const;
    bool is_left_pressed() const;
    bool is_right_pressed() const;
    bool is_key_pressed(char key) const;

    void process_key(uint8_t key, bool pressed);
    void set_mouse_button_state(bool left_pressed, bool right_pressed);
    void set_mouse_pos(int x, int y);

private:
    PointI _mouse_pos;
    bool _left_pressed = false;
    bool _right_pressed = false;
    std::unordered_map<char, std::function<void()>> _key_states;
    bool _key_pressed[256] = {false};
};
