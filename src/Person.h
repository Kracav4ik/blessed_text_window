#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Person : public GameObject, public Renderable {
public:
    explicit Person(GameScreen& game_screen);

    void process(float elapsed) override;

    void render() const override;

    void take_damage(int damage);
    void heal(int value);
    bool was_damaged() const;
    int health_points() const;

    bool is_alive() const;
    float vision_value();

private:
    float _shot_elapsed = 0;
    int _health_points = 100;
    bool _was_damaged = false;
    float _vision_value = 10;
};
