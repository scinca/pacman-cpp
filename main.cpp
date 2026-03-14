#include <ctime>

#include "Game/Game.h"
#include "config.h"
#include "GameMenu/GameMenu.h"

int main(int argc, char* argv[]) {
    InitWindow(WindowConfig::WindowWidth, WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));
    Game game;
    GameMenu game_menu(&game);


    //  game.Initialize();

    while (!game.ShouldClose()) {
        BeginDrawing();
        if (!game.HasStarted()) {
            // Menu drawing
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
