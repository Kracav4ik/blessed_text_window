#include "GameManager.h"
#include "InputManager.h"

using namespace std::chrono;

void GameManager::init() {
    _person = std::make_unique<Person>();

    InputManager::get().add_action('Q', [this]() {
        _running = false;
    });

    _now = system_clock::now();
    _running = true;
}

bool GameManager::running() {
    return _running;
}

void GameManager::process() {
    auto now = system_clock::now();
    float elapsed = duration_cast<microseconds>(now - _now).count() * 1.e-6f;
    _now = now;

    for (const auto& object : _objects) {
        object->process(elapsed);
    }
}
