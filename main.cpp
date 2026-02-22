#include <iostream>
#include <raylib.h>

namespace WindowConfig {
    std::int32_t WindowWidth = 1600;
    std::int32_t WindowHeight = 900;
    std::string WindowTitle = "Raylib Pacman Game";
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle.c_str()); // c_str is required because Raylib is written in C and expects a char* string.
   SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible
        EndDrawing();
    }
    return 0;
}
