#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Missile : public GameObject, public Renderable {
public:
    explicit Missile(GameScreen& game_screen);

    void process(float elapsed) override;

    void set_pos(const PointF& new_pos) override;
    void set_grid_pos(const PointI& new_pos) override;

    void render() const override;

    void direct_velocity(const PointF& direction);

private:
    PointF _old_pos;
    bool processed = false;
};
