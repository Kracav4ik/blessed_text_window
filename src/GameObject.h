#pragma once

#include "utils.h"

class GameObject {
public:
    GameObject();
    explicit GameObject(const PointI& grid_pos);

    virtual void process(float elapsed);

    virtual const PointF& pos() const;
    virtual void set_pos(const PointF& pos);

    virtual const PointI& grid_pos() const;
    virtual void set_grid_pos(const PointI& pos);

    virtual const PointF& velocity() const;
    virtual void set_velocity(const PointF& velocity);

    virtual ~GameObject();

protected:
    PointF _pos;
    PointF _velocity;

    PointI _grid_pos;

private:
    void install();
};
