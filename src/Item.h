#pragma once

#include "GameObject.h"
#include "Renderable.h"

class Item : public GameObject, public Renderable {
public:
    Item(GameScreen& game_screen, int healing_value);

    void process(float elapsed) override;

    void render() const override;

    void set_visible(bool visible) override;

private:
    int _healing_value;
};
