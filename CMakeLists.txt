cmake_minimum_required(VERSION 4.1)
project(pacman_cpp)

set(CMAKE_CXX_STANDARD 23)

# Try to find raylib installed on system first then download
find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message(STATUS "raylib not found on system, fetching from GitHub...")
    include(FetchContent)

    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
    )

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

# Fetch raygui
include(FetchContent)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
)
FetchContent_MakeAvailable(raygui)

# Create raygui library
add_library(raygui SHARED ${raygui_SOURCE_DIR}/src/raygui.h)
set_target_properties(raygui PROPERTIES
        LINKER_LANGUAGE C
)
target_include_directories(raygui PUBLIC ${raygui_SOURCE_DIR}/src)
target_compile_definitions(raygui PUBLIC RAYGUI_IMPLEMENTATION)
target_link_libraries(raygui PUBLIC raylib)

add_executable(pacman_cpp main.cpp
        config.h
        map/map.cpp
        map/map.h
        players/player_base.h
        time/deltaTime.cpp
        time/deltaTime.h
        players/player_base.cpp
        players/HumanPlayer/HumanPlayer.cpp
        players/HumanPlayer/HumanPlayer.h
        players/EnemyAI/EnemyPlayer.cpp
        players/EnemyAI/EnemyPlayer.h
)

target_link_libraries(pacman_cpp raylib raygui)

# Release build flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(pacman_cpp PRIVATE -O2)
endif()