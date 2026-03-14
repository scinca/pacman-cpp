#include "Game/Game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.Initialize();

    while (!game.ShouldClose()) {
        game.ProcessInput();
        game.Update();
        game.Draw();
    }

    return 0;
}