#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Enemy : public GameObject, public Renderable {
public:
    void process(float elapsed) override;

    void render() override;
};
