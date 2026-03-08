#include <iostream>
#include <raylib.h>
#include <ctime>
#include "config.h"
#include "map/map.h"
#include "players/EnemyAI/EnemyPlayer.h"
#include "players/HumanPlayer/HumanPlayer.h"
#include "time/deltaTime.h"

int main() {
    const std::string default_filename { "./assets/default_map.txt"}; // maybe I'll implement a map selection system later.

    InitWindow(WindowConfig::WindowWidth,WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));
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
    const int player_starting_position = game_map.FindPlayerStartTile();
    const std::vector<int>enemy_starting_positions = game_map.FindEnemyStartTiles();

    auto player = HumanPlayer(&game_map, &Timer, player_starting_position, YELLOW);
    auto red_enemy = EnemyPlayer(&game_map, &Timer, &player, enemy_starting_positions[0], RED);
    auto blue_enemy = EnemyPlayer(&game_map, &Timer, &player, enemy_starting_positions[1],SKYBLUE);

    while (!WindowShouldClose()) {
        Timer.CalculateDeltaTime();
        if (game_map.AllExplored()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("You won!", 100,100, 40, BLACK);
            EndDrawing();
        }
        else if (!player.CheckIfAlive()){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("You lost.", 100,100, 40, BLACK);
            EndDrawing();
        }
        else{
            BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangleLines(1,1, WindowConfig::WindowWidth -1 ,WindowConfig::WindowHeight -1, RAYWHITE); // tiny inset is required so border is visible.
            game_map.Draw();

            if (IsKeyDown(KEY_UP )||IsKeyDown(KEY_W)) {
                player.SetNextDirection(Direction::UP);
            }
            else if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)) {
                player.SetNextDirection(Direction::DOWN);
            }
            else if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) {
                player.SetNextDirection(Direction::LEFT);
            }
            else if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) {
                player.SetNextDirection(Direction::RIGHT);
            }

            player.Move();
            player.Draw();
            red_enemy.Move();
            red_enemy.Draw();
            blue_enemy.Move();
            blue_enemy.Draw();


            EndDrawing();
        }
    }
    return 0;
}

