#include <iostream>
#include "Database/Database.h"
#include "Game/Game.h"
#include "GameMenu/GameMenu.h"
#include "ApplicationConfig.h"
#include "MapCreator/MapCreator.h"

int main() {

    ApplicationConfig::GetInstance();
    Database database;
    Game game{&database};
    MapCreator map_creator{&database, &game};
    GameMenu game_menu{&game, &map_creator, &database};



    while (!WindowShouldClose()) {
        BeginDrawing();
        if (!game.HasStarted()) {
            if (game.StartedAsTest() && !map_creator.IsActive()) {
                map_creator.Initialize();
            }
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
