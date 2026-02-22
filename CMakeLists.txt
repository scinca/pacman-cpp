cmake_minimum_required(VERSION 4.1)
project(pacman_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(pacman_cpp main.cpp
        config.h)

find_package(raylib REQUIRED)
target_link_libraries(pacman_cpp raylib)