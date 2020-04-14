#pragma once
#include "Screen.h"
#include "Singleton.h"
#include "ObjectManager.h"

class Missile;
class GameScreen;

class ScreenManager : public Singleton<ScreenManager>, public ObjectManager<Screen> {
SINGLETON_CTOR(ScreenManager)
public:
    void init();
    void destruct();
    void process(float elapsed);
    void render() const;
    void restart();

    void game_over();

    virtual ~ScreenManager();
};
