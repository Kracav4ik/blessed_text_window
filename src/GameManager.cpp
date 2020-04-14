#include "GameManager.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include <chrono>

using namespace std::chrono;

void GameManager::init() {
    InputManager::get().add_action('Q', [this]() {
        _running = false;
    });

    _now = system_clock::now();
    _running = true;
}

bool GameManager::running() const {
    return _running;
}

void GameManager::process() {
    auto now = system_clock::now();
    float elapsed = duration_cast<microseconds>(now - _now).count() * 1.e-6f;
    _now = now;
    ScreenManager::get().process(elapsed);
}
