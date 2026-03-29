#include <ctime>
#include <iostream>
#include "Database/Database.h"
#include "Game/Game.h"
#include "GameMenu/GameMenu.h"
#include "ApplicationConfig.h"

int main(int argc, char* argv[]) {

    Database database;
    ApplicationConfig::GetInstance();


    ToggleFullscreen();
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));

    Game game{&database};
    const GameMenu game_menu{&game};



    while (WindowShouldClose()) {
        BeginDrawing();
        if (!game.HasStarted()) {
            ClearBackground(RAYWHITE);
            game_menu.Show();
        }else{
            game.HandlePlayerInput();
            game.Update();
            game.DrawFrame();
        }
        EndDrawing();

    }
    // WindowConfig destructor closes window
    return 0;
}
