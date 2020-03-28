#pragma once

#include "Singleton.h"
#include "ObjectManager.h"
#include "utils.h"

#include <chrono>
#include <memory>

class GameObject;
class Person;
class Enemy;

class GameManager : public Singleton<GameManager>, public ObjectManager<GameObject> {
SINGLETON_CTOR_DECL(GameManager)
public:
    ~GameManager();
    void init();
    bool running();

    void process();
    PointI player_pos();
    bool can_pass(const PointI& p) const;

private:
    bool _running = false;
    std::unique_ptr<Person> _person;
    std::chrono::system_clock::time_point _now;
    std::vector<std::unique_ptr<Enemy>> _enemies;

    void generate_enemy();
};
