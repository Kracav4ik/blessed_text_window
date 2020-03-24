#pragma once

#include "Person.h"
#include "Singleton.h"
#include "ObjectManager.h"

#include <chrono>
#include <memory>

class GameManager : public Singleton<GameManager>, public ObjectManager<GameObject> {
SINGLETON_CTOR(GameManager)
public:
    void init();
    bool running();

    void process();
    Point player_pos();
    bool can_pass(const Point& p) const;

private:
    bool _running = false;
    std::unique_ptr<Person> _person;
    std::chrono::system_clock::time_point _now;

    void generate_enemy();
};
