#pragma once

#include "GameObject.h"
#include "Renderable.h"
#include "utils.h"

class Person : public GameObject, public Renderable {
private:
    Point _pos;
    Point _velocity;
public:
    Person() = default;

    void process(float elapsed) override;

    void render() override;

    const Point& pos() const;
    Point& pos();
    void set_pos(const Point& pos);

    const Point& velocity() const;
    Point& velocity();
    void set_velocity(const Point& velocity);
};
