#pragma once

#include "Screen.h"

#include <memory>
#include <unordered_set>

class GameObject;
class Person;
class Enemy;
class Missile;

class GameScreen: public Screen {
public:
    GameScreen(const PointI& pos, const PointI& size);

    void process(float elapsed) override;

    void add_game_object(GameObject* object);
    void remove_game_object(GameObject* object);

    void delete_later(std::unique_ptr<GameObject>&& object);
    void delete_objects();

    PointI player_pos();
    bool can_pass(const PointI& p, std::unordered_set<GameObject*> ignore = {}) const;
    void kill(const Missile& missile, const PointI& target);
    void launch_missile(const PointI& target);

private:
    std::unique_ptr<Person> _person;
    std::vector<std::unique_ptr<GameObject>> _to_delete;
    std::vector<std::unique_ptr<Enemy>> _enemies;
    std::vector<std::unique_ptr<Missile>> _missiles;
    std::vector<GameObject*> _game_objects;

    void generate_enemy();
};
