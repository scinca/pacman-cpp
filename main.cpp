#include <iostream>
#include <raylib.h>
#include "config.h"
#include "map/map.h"
#include "players/HumanPlayer/HumanPlayer.h"
#include "time/deltaTime.h"

int main() {
    const std::string default_filename { "./assets/default_map.txt"}; // maybe I'll implement a map selection system later.

    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);

    Time Timer;
    Map game_map;
    auto loading_result { game_map.load(default_filename)};
    if (!loading_result) {
        // error returns since I don't have any way to do it better.
        const std::string_view loading_error = loading_result.error();
        std::cerr << "Failed to load map: " << loading_error << "\n";
        return 1;
    }else {
        std::cout << "Map loaded successfully\n"; // for debugging might remove this later.
    }
    HumanPlayer player = HumanPlayer(&game_map, &Timer);
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible.
        game_map.draw();

        if (IsKeyDown(KEY_UP))         player.move(Direction::UP);
        else if (IsKeyDown(KEY_DOWN))  player.move(Direction::DOWN);
        else if (IsKeyDown(KEY_LEFT))  player.move(Direction::LEFT);
        else if (IsKeyDown(KEY_RIGHT)) player.move(Direction::RIGHT);
        else                           player.move();
        player.draw();
        EndDrawing();
    }
    return 0;
}


