#pragma once

class Renderable {
public:
    Renderable();

    virtual void render() = 0;

    virtual ~Renderable();

    bool is_danger_theme() const;
};
