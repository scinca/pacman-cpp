#ifndef GAME_H
#define GAME_H

#include <memory>
#include <optional>

#include "../Map/Map.h"
#include "HumanPlayer/HumanPlayer.h"
#include "EnemyAI/EnemyPlayer.h"
#include "Time/DeltaTime.h"
#include "Database/Database.h"

enum class GameState {
    PLAYING,
    WON,
    LOST,
    PAUSED,
};

class Game {
public:
    explicit Game(Database* db);



    ~Game();

    void Initialize(std::optional<int> map_number = 1);
    void HandlePlayerInput();
    void Update();
    void DrawFrame();

    [[nodiscard]] bool HasStarted() const;

    void SetCurrentMapNumber(const int number) {last_played_map_number_ = number;}
    void Pause();
    void Resume();
    void Stop(){is_game_running_ = false;}
    void AddSilentPause(){ silent_pause_ = true; }
private:
    void DrawWinScreen();
    void DrawLoseScreen();

    Database* db_{};
    GameState state;
    Time time;
    Map game_map;
    int last_played_map_number_ {1};
    std::unique_ptr<HumanPlayer> player;
    bool is_game_running_{};
    std::vector<std::unique_ptr<EnemyPlayer>> enemy_players;
    const std::vector<Color>enemy_colors = {RED, SKYBLUE, PINK, LIME};
    bool silent_pause_ = true;

};

#endif // GAME_H