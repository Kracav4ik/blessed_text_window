cmake_minimum_required(VERSION 3.14)
project(blessed_text_window)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif()

include_directories(src)
include_directories(thirdparty/PDCurses-3.8)

add_subdirectory(src)
add_subdirectory(thirdparty/PDCurses-3.8)

