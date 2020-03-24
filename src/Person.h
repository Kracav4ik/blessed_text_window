#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Person : public GameObject, public Renderable {
public:
    Person() = default;

    void process(float elapsed) override;

    void render() override;
};
