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


include(FetchContent)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0
)
FetchContent_MakeAvailable(raygui)

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
        Game/Game.cpp
        Game/Game.h
        GameMenu/GameMenu.cpp
        GameMenu/GameMenu.h
        third_party/sqlite/sqlite3.h
        Database/Database.cpp
        Database/Database.h
)

# Add raygui include directory
target_include_directories(pacman_cpp PRIVATE ${raygui_SOURCE_DIR}/src)
add_library(sqlite3_lib STATIC third_party/sqlite/sqlite3.c
        third_party/sqlite/sqlite3.h)
target_include_directories(sqlite3_lib PUBLIC third_party/sqlite)
target_link_libraries(pacman_cpp raylib sqlite3_lib)

# Release build flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(pacman_cpp PRIVATE -O2)
endif()