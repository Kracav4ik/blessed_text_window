#pragma once

#include "Screen.h"

class GameOverScreen: public Screen {
public:
    GameOverScreen(const PointI& pos, const PointI& size);

    void process(float elapsed) override;

    void render() const override;
};
