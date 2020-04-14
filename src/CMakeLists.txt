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
        InputManager.cpp
        InputManager.h
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

add_executable(${EXE_NAME} ${EXE_SOURCES})
