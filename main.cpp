#include <iostream>
#include <raylib.h>
#include "config.h"
#include "map.h" // for the game map class


int main() {
    const std::string default_filename { "./assets/default_map.txt"};

    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);
    Map game_map;
    auto loading_result = game_map.load(default_filename);
    if (!loading_result) {
        // result contains an error
        const std::string_view loading_error = loading_result.error();
        std::cerr << "Failed to load map: " << loading_error << "\n";
        // handle error (e.g., exit or fallback)
    }else {
        std::cout<< "Map loaded successfully\n";
    }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible
       // DrawRectangle(WindowConfig::WindowRoot,WindowConfig::WindowRoot, TileWidth, TileWidth, RAYWHITE);
        game_map.draw();

        EndDrawing();
    }
    return 0;
}
