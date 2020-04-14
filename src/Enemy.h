#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Enemy : public GameObject, public Renderable {
public:
    Enemy(GameScreen& game_screen, float damage, char type);

    void process(float elapsed) override;
    void render() const override;
    float damage() const;
    bool can_act() const;

private:
    float _hit_elapsed = 0;
    float _damage;
    char _type;
};
