#include <ctime>
#include <iostream>
#include <ostream>

#include "Database/Database.h"
#include "third_party/sqlite/sqlite3.h"
#include "Game/Game.h"
#include "config.h"
#include "GameMenu/GameMenu.h"

int main(int argc, char* argv[]) {

    Database database;

    InitWindow(WindowConfig::WindowWidth, WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));
    Game game{ & database};
    const GameMenu game_menu{&game};



    while (!Game::ShouldClose()) {
        BeginDrawing();
        if (!game.HasStarted()) {

            ClearBackground(RAYWHITE);
            game_menu.ShowMenu();
        }else{
            game.ProcessInput();
            game.Update();
            game.DrawFrame();
        }

        EndDrawing();

    }
    CloseWindow();
    return 0;
}
