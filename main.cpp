#include <iostream>
#include <raylib.h>
#include "config.h"

constexpr std::int32_t TileWidth { 32 };

int main() {
    std::cout << "Hello, World!" << std::endl;
    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle);
   SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible
        DrawRectangle(WindowConfig::WindowRoot,WindowConfig::WindowRoot, TileWidth, TileWidth, RAYWHITE);
        EndDrawing();
    }
    return 0;
}
