#pragma once

class Renderable {
public:
    Renderable();

    virtual void render() = 0;

    virtual ~Renderable();
};
