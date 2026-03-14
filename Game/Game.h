#ifndef GAME_H
#define GAME_H

#include <memory>
#include "../map/map.h"
#include "../players/HumanPlayer/HumanPlayer.h"
#include "../players/EnemyAI/EnemyPlayer.h"
#include "../time/deltaTime.h"

enum class GameState {
    PLAYING,
    WON,
    LOST
};

class Game {
public:
    Game();
    ~Game();

    void Initialize();
    void ProcessInput() const;
    void Update();
    void DrawFrame();

    static bool ShouldClose();

private:
    static void DrawWinScreen();
    void DrawLoseScreen();

    GameState state;
    Time time;
    Map game_map;
    std::unique_ptr<HumanPlayer> player;
    std::unique_ptr<EnemyPlayer> red_enemy;
    std::unique_ptr<EnemyPlayer> blue_enemy;


};

#endif // GAME_H