#pragma once

#include "Person.h"
#include "Singleton.h"
#include "ObjectManager.h"

#include <chrono>
#include <memory>

class GameManager : public Singleton<GameManager>, public ObjectManager<GameObject> {
SINGLETON_CTOR(GameManager)
private:
    bool _running = false;
    std::unique_ptr<Person> _person;
    std::chrono::system_clock::time_point _now;

public:
    void init();
    bool running();

    void process();
};
