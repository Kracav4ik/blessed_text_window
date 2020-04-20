#pragma once


#include "utils.h"

#include <vector>
#include <unordered_set>

class Renderable;
class Missile;

class Screen {
public:
    Screen(const PointI& pos, const PointI& size, char bgSing);

    void add_renderable(Renderable* object);
    void remove_renderable(Renderable* object);
    void fill_bg(PointI pos = {}, float range = -1) const;

    virtual void process(float elapsed) = 0;
    virtual void render() const;

    virtual ~Screen();

    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    int width() const;
    int height() const;

protected:
    // background character
    char _bg_sing;

    PointI _pos;
    PointI _size;
    std::vector<Renderable*> _renderables;
};
