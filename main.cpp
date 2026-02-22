#include <iostream>
#include <raylib.h>
#include "config.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle));
   SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible
        EndDrawing();
    }
    return 0;
}
