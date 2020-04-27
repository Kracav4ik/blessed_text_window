#include "InputManager.h"
#include "ScreenManager.h"
#include "RenderManager.h"
#include "GameManager.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <curses.h>
#endif

void main_loop() {
    if (!GameManager::get().running()) {
        return;
    }
    InputManager::get().check_input();
    GameManager::get().process();
    RenderManager::get().render();
}

#ifdef __EMSCRIPTEN__
extern "C"
#endif


int main() {
    RenderManager::get().init();
    ScreenManager::get().init();
    InputManager::get().init();
    GameManager::get().init();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (GameManager::get().running()) {
        InputManager::get().check_input();
        GameManager::get().process();
        RenderManager::get().render();
        napms(50);
    }
#endif
    return 0;
}
