#pragma once

class Screen;

class Renderable {
public:
    explicit Renderable(Screen& screen);

    virtual void render() const = 0;

    virtual ~Renderable();

    bool is_danger_theme() const;

protected:
    Screen& _screen;
};
