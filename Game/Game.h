#ifndef GAME_H
#define GAME_H

#include <memory>
#include <optional>

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

    void Initialize(const std::optional<std::string> &map_path = std::nullopt);
    void ProcessInput() const;
    void Update();
    void DrawFrame();

    bool HasStarted() const;

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
    bool is_game_running_;
    std::vector<std::unique_ptr<EnemyPlayer>> enemy_players;
    std::vector<Color>enemy_colors = {RED, SKYBLUE, PINK, LIME};


};

#endif // GAME_H