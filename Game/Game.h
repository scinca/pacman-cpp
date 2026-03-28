#ifndef GAME_H
#define GAME_H

#include <memory>
#include <optional>

#include "../Map/Map.h"
#include "../players/HumanPlayer/HumanPlayer.h"
#include "../players/EnemyAI/EnemyPlayer.h"
#include "../time/deltaTime.h"
#include "../Database/Database.h"

enum class GameState {
    PLAYING,
    WON,
    LOST
};

class Game {
public:
    Game(Database* db);



    ~Game();

    void Initialize(std::optional<int> map_number = 1);
    void HandlePlayerInput() const;
    void Update();
    void DrawFrame();

    bool HasStarted() const;

    static bool ShouldClose();
    void SetCurrentMapNumber(const int number) {current_map_number_ = number;}

private:
    static void DrawWinScreen();
    void DrawLoseScreen();

    Database* db_{};
    GameState state;
    Time time;
    Map game_map;
    int current_map_number_ {1};
    std::unique_ptr<HumanPlayer> player;
    std::unique_ptr<EnemyPlayer> red_enemy;
    std::unique_ptr<EnemyPlayer> blue_enemy;
    bool is_game_running_{};
    std::vector<std::unique_ptr<EnemyPlayer>> enemy_players;
    std::vector<Color>enemy_colors = {RED, SKYBLUE, PINK, LIME};

};

#endif // GAME_H