#include "InputManager.h"
#include "RenderManager.h"
#include "GameManager.h"

#include <curses.h>


int main() {
    RenderManager::get().init();
    InputManager::get().init();
    GameManager::get().init();

    while (GameManager::get().running()) {
        InputManager::get().check_input();
        GameManager::get().process();
        RenderManager::get().render();
        napms(50);
    }
}
