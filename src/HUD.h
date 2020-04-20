#pragma once
#include "Singleton.h"

#include <string>

class GameScreen;

class HUD : public Singleton<HUD> {
SINGLETON_CTOR(HUD)
public:
    void process(float elapsed);
    void render(const GameScreen& scr) const;
    void set_text(const std::string& text, float seconds = 10);

private:
    std::string _text;
    float _show_elapsed = 0;
};
