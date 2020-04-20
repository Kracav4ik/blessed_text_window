#pragma once

#include "Singleton.h"
#include "utils.h"

#include <chrono>

class GameManager : public Singleton<GameManager> {
SINGLETON_CTOR(GameManager)
public:
    void init();
    bool running() const;

    void process();
private:
    bool _running = false;
    std::chrono::system_clock::time_point _now;
};
