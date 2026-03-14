#include <ctime>

#include "Game/Game.h"
#include "config.h"

int main(int argc, char* argv[]) {
    InitWindow(WindowConfig::WindowWidth, WindowConfig::WindowHeight, WindowConfig::WindowTitle);
    SetTargetFPS(60);
    SetRandomSeed(static_cast<unsigned int>(std::time(nullptr)));

    Game game;

    game.Initialize();

    while (!game.ShouldClose()) {
        game.ProcessInput();
        game.Update();
        game.DrawFrame();
    }

    return 0;
}