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
    auto loading_result { game_map.Load(default_filename)};
    if (!loading_result) {
        // error returns since I don't have any way to do it better.
        const std::string_view loading_error = loading_result.error();
        std::cerr << "Failed to load map: " << loading_error << "\n";
        return 1;
    }else {
        std::cout << "Map loaded successfully\n"; // for debugging might remove this later.
    }
    auto player = HumanPlayer(&game_map, &Timer);

    while (!WindowShouldClose()) {
        if (game_map.AllExplored()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("You won!", 100,100, 40, BLACK);
            EndDrawing();
        }
        else if (!player.CheckIfAlive()){
            BeginDrawing();
            DrawText("You lost.", 100,100, 40, BLACK);
            EndDrawing();
        }
        else{
            BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible.
            game_map.Draw();

            if (IsKeyDown(KEY_UP)) {
                player.SetNextDirection(Direction::UP);
            }
            else if (IsKeyDown(KEY_DOWN)) {
                player.SetNextDirection(Direction::DOWN);
            }
            else if (IsKeyDown(KEY_LEFT)) {
                player.SetNextDirection(Direction::LEFT);
            }
            else if (IsKeyDown(KEY_RIGHT)) {
                player.SetNextDirection(Direction::RIGHT);
            }

            player.Move();

            player.Draw();
            EndDrawing();
        }
    }
    return 0;
}

