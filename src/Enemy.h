#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Enemy : public GameObject, public Renderable {
public:
    Enemy(GameScreen& game_screen, int damage, int hp, char type);

    void process(float elapsed) override;
    void render() const override;
    int damage() const;
    int health_points() const;
    bool can_act() const;
    void take_damage(int damage);

private:
    float _hit_elapsed = 0;
    int _damage;
    int _health_points;
    char _type;
};
