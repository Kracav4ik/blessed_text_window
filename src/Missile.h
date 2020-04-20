#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Missile : public GameObject, public Renderable {
public:
    Missile(GameScreen& game_screen, int damage);

    void process(float elapsed) override;

    void set_pos(const PointF& new_pos) override;
    void set_grid_pos(const PointI& new_pos) override;

    void render() const override;

    void direct_velocity(const PointF& direction);
    int damage() const;

private:
    PointF _old_pos;
    bool _processed = false;
    int _damage;
};
