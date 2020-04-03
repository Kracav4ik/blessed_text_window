#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Missile : public GameObject, public Renderable {
public:
    void process(float elapsed) override;

    void render() override;

    void direct_velocity(const PointF& direction);
};
