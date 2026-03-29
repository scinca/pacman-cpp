#include <ctime>
#include <iostream>
#include "Database/Database.h"
#include "Game/Game.h"
#include "GameMenu/GameMenu.h"
#include "ApplicationConfig.h"
#include "MapCreator/MapCreator.h"

int main(int argc, char* argv[]) {

    Database database;
    ApplicationConfig::GetInstance();
    MapCreator map_creator{&database};


    ToggleFullscreen();
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));

    Game game{&database};
    const GameMenu game_menu{&game, &map_creator};



    while (!WindowShouldClose()) {
        BeginDrawing();
        if (!game.HasStarted()) {
            if (map_creator.IsActive()) {
                map_creator.HandlePlayerInput();
                map_creator.DrawFrame();

            }else {
                ClearBackground(RAYWHITE);
                game_menu.Show();
            }

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
