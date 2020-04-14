#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Person : public GameObject, public Renderable {
public:
    explicit Person(GameScreen& game_screen);

    void process(float elapsed) override;

    void render() const override;

    void take_damage(float damage);
    bool was_damaged() const;

    bool is_alive() const;

private:
    float _shot_elapsed = 0;
    float _heal_points = 100;
    bool _was_damaged = false;
};
