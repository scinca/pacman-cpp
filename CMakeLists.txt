cmake_minimum_required(VERSION 4.1)
project(pacman_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(pacman_cpp main.cpp
        config.h
        map/map.cpp
        map/map.h
        players/player_base.h
        time/deltaTime.cpp
        time/deltaTime.h
        players/player_base.cpp
)

find_package(raylib REQUIRED)
target_link_libraries(pacman_cpp raylib)

# copy assets folder to the build directory (Made by Claude because I didn't know of an elegant way to make this.
# In a future version I might remove an assets directory and move to cpp variables.
add_custom_command(
        TARGET pacman_cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:pacman_cpp>/assets
)