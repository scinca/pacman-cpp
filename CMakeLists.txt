cmake_minimum_required(VERSION 4.1)
project(pacman_cpp)

set(CMAKE_CXX_STANDARD 23)

# Release build flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(pacman_cpp PRIVATE -O2)
endif()

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

find_package(raylib REQUIRED)
target_link_libraries(pacman_cpp raylib)

