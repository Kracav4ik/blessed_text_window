set(EXE_NAME blessed_text_window)

set(EXE_SOURCES
        Enemy.cpp
        Enemy.h
        GameManager.cpp
        GameManager.h
        GameObject.cpp
        GameObject.h
        GameOverScreen.cpp
        GameOverScreen.h
        GameScreen.cpp
        GameScreen.h
        HUD.cpp
        HUD.h
        InputManager.cpp
        InputManager.h
        Item.cpp
        Item.h
        main.cpp
        Missile.cpp
        Missile.h
        ObjectManager.h
        ObjectManager.hpp
        Person.cpp
        Person.h
        Renderable.cpp
        Renderable.h
        RenderManager.cpp
        RenderManager.h
        Screen.cpp
        Screen.h
        ScreenManager.cpp
        ScreenManager.h
        Singleton.h
        utils.cpp
        utils.h
        utils.hpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(EXE_SOURCES
            ${EXE_SOURCES}

            pdcurses-emscripten/pdcdisp.c
            pdcurses-emscripten/pdcgetsc.c
            pdcurses-emscripten/pdckbd.c
            pdcurses-emscripten/pdcscrn.c
            pdcurses-emscripten/pdcsetsc.c
            pdcurses-emscripten/pdcutil.c
    )
endif()

add_executable(${EXE_NAME} ${EXE_SOURCES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "-s EXPORTED_FUNCTIONS=[_main,_keydown_handler,_keyup_handler,_mouse_down_handler,_mouse_up_handler,_mouse_move_handler] -s EXTRA_EXPORTED_RUNTIME_METHODS=[cwrap] -s LLD_REPORT_UNDEFINED")

    add_custom_target(copy-html-src ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src-html ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    add_dependencies(${EXE_NAME} copy-html-src)
endif()
