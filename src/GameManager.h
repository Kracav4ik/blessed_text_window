#pragma once

#include "Singleton.h"
#include "ObjectManager.h"
#include "utils.h"

#include <chrono>
#include <memory>

class GameObject;
class Person;
class Enemy;
class Missile;

class GameManager : public Singleton<GameManager>, public ObjectManager<GameObject> {
SINGLETON_CTOR_DECL(GameManager)
public:
    ~GameManager();
    void init();
    bool running();

    void process();

    void delete_later(std::unique_ptr<GameObject>&& object);
    void delete_objects();

    PointI player_pos();
    bool can_pass(const PointI& p) const;
    void kill(const Missile& missile, const PointI& target);
    void launch_missile(const PointI& target);

private:
    bool _running = false;
    std::unique_ptr<Person> _person;
    std::chrono::system_clock::time_point _now;
    std::vector<std::unique_ptr<GameObject>> _to_delete;
    std::vector<std::unique_ptr<Enemy>> _enemies;
    std::vector<std::unique_ptr<Missile>> _missiles;

    void generate_enemy();
};
