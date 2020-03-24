set(EXE_NAME blessed_text_window)

set(EXE_SOURCES
        GameManager.cpp
        GameManager.h
        InputManager.cpp
        InputManager.h
        main.cpp
        Renderable.h
        Renderable.cpp
        RenderManager.cpp
        RenderManager.h
        Singleton.h
        Person.cpp
        Person.h
        utils.h
        GameObject.cpp ObjectManager.hpp ObjectManager.h
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
