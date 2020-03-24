#pragma once

#include "utils.h"

class GameObject {
public:
    GameObject();
    GameObject(const Point& pos);

    virtual void process(float elapsed) = 0;

    virtual const Point& pos() const;
    virtual Point& pos();
    virtual void set_pos(const Point& pos);

    virtual const Point& velocity() const;
    virtual Point& velocity();
    virtual void set_velocity(const Point& velocity);
    void fix_pos();

    virtual ~GameObject();
protected:
    Point _old_pos;
    Point _pos;
    Point _velocity;

private:
    void init();
};
