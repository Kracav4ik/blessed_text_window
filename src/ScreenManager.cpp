#include "ScreenManager.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "utils.hpp"

#include <curses.h>

void ScreenManager::init() {
    auto screen = new GameScreen({0, 2}, {COLS, LINES - 4});
}

void ScreenManager::destruct() {
    for (auto& object : get_objects()) {
        delete object;
    }
}

void ScreenManager::process(float elapsed) {
    get_objects().back()->process(elapsed);
}

void ScreenManager::render() const {
    for (const auto& screen : get_objects()) {
        screen->render();
    }
}

void ScreenManager::restart() {
    destruct();
    init();
}

void ScreenManager::game_over() {
    int width = 40;
    int height = 18;
    auto screen = new GameOverScreen({(COLS - width) / 2, (LINES - height) / 2}, {width, height});
}

ScreenManager::~ScreenManager() {
    destruct();
}
