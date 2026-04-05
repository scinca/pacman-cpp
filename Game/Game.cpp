//
// Created by simon on 14.03.26.
//


#include <iostream>
#include <raygui.h>
#include <raylib.h>
#include "Game.h"
#include "../ApplicationConfig.h"



Game::Game(Database *db) : db_(db), state(GameState::PLAYING), game_map(db_) {
}

Game::~Game() = default;

void Game::Initialize(const std::optional<int> map_number, const std::optional<std::string>& map_data) {

    if (map_data.has_value()) {
        game_map.LoadFromString(map_data.value());
    }
    else if (map_number.has_value()) {
        last_played_map_number_ = map_number.value();
        game_map.LoadMapFromDB(map_number.value());
    }
    else {
        game_map.LoadMapFromDB(last_played_map_number_);
   }

    HideCursor();
    enemy_players.clear();
    is_game_running_ = true;

    const int player_starting_position = game_map.FindPlayerStartTile();
    const std::vector<int> enemy_starting_positions = game_map.FindEnemyStartTiles();
    player = std::make_unique<HumanPlayer>(&game_map, &time_, player_starting_position, YELLOW);
    for (int i = 0; i < enemy_starting_positions.size(); i++) {
        enemy_players.push_back(std::make_unique<EnemyPlayer>(&game_map, &time_, player.get(), enemy_starting_positions[i], enemy_colors[i]));
    }
    
    silent_pause_ = true;
    state = GameState::PLAYING;
}

void Game::HandlePlayerInput() {
    if (silent_pause_) {
        if (IsKeyPressed(KEY_W)||IsKeyPressed(KEY_A)|| IsKeyPressed(KEY_S)|| IsKeyPressed(KEY_D) || IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_DOWN)|| IsKeyPressed(KEY_LEFT)|| IsKeyPressed(KEY_RIGHT)) {
            silent_pause_ = false;
            Resume();
        }
    }
    if (state != GameState::PLAYING) {
        if (IsKeyPressed(KEY_P)&& state == GameState::PAUSED) {
             Resume();
        }
        return;
    }
    if (IsKeyPressed(KEY_P)) {
        Pause();
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        player->SetNextDirection(Direction::UP);
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        player->SetNextDirection(Direction::DOWN);
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->SetNextDirection(Direction::LEFT);
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->SetNextDirection(Direction::RIGHT);
    }

}

void Game::Update() {
    if (silent_pause_) {
        return;
    }
    if (state != GameState::PLAYING) {
        return;
    }

    time_.CalculateDeltaTime();

    if (game_map.AllExplored()) {
        state = GameState::WON;
    }
    else if (!player->CheckIfAlive()) {
        state = GameState::LOST;
    }
    else {
        player->Move();
        const int tile = player->GetCurrentTile();
        for (const auto& enemy : enemy_players) {
            enemy->Move();
            if (enemy->GetCurrentTile()== tile) {
                player->Kill();
                if (!player->CheckIfAlive()) {
                    state = GameState::LOST;
                }
                player->ResetPosition();
                silent_pause_ = true;
                for (const auto& other_enemy : enemy_players) {
                    other_enemy->ResetPosition();
                }


            }
        }
    }
}



void Game::Pause() {
    time_.PauseGameTimer();
    state = GameState::PAUSED;
    ShowCursor();
}
void Game::Resume() {
    time_.StartGameTimer();
    state = GameState::PLAYING;
    HideCursor();
}

void Game::DrawFrame() {
    const auto& config = ApplicationConfig::GetInstance();
    DrawRectangleLines(config.WindowRoot,config.WindowRoot, GetScreenWidth()-1,GetScreenHeight()-1, RAYWHITE);
    switch (state) {
        case GameState::PLAYING: {
            ClearBackground(BLACK);
            for (int i = 1; i <= player->GetMaxLives(); i++) {
                if (i <= player->GetRemainingLives()) {
                    DrawCircle(config.WindowRoot + 100 + i * 30, config.WindowRoot + 80, config.PointRadius, RED);
                }else {
                    DrawCircleLines(config.WindowRoot+ 100+  i* 30, config.WindowRoot+80,config.PointRadius, RED);
                }

            if (silent_pause_) {
                DrawFPS(config.WindowRoot + 5, config.WindowRoot+5);
                DrawText("The game hasn't started, press any of the Direction Keys to continue",config.WindowRoot + 5, config.WindowRoot+20, config.font_size, SKYBLUE);
                if (IsKeyPressed(KEY_W)||IsKeyPressed(KEY_A)|| IsKeyPressed(KEY_S)|| IsKeyPressed(KEY_D) || IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_DOWN)|| IsKeyPressed(KEY_LEFT)|| IsKeyPressed(KEY_RIGHT)) {
                    silent_pause_ = false;
                    Resume();
                }
                game_map.Draw(false);
                player->Draw();
                for (const auto& enemy : enemy_players) {
                    enemy->Draw();
                }
            }else {
                DrawFPS(config.WindowRoot + 5, config.WindowRoot+5);
                DrawText(std::format("Your current score: {} / {}", game_map.GetExploredTileCount(), game_map.GetFreeTileCount()).c_str(),config.WindowRoot + 5, config.WindowRoot+20, config.font_size, SKYBLUE);
            }
                game_map.Draw(false);
                player->Draw();
                for (const auto& enemy : enemy_players) {
                    enemy->Draw();
                }
            }
            break;
        }

        case GameState::PAUSED: {
                ClearBackground(RAYWHITE);
                DrawText("Game is paused, click P to continue", 100, 100, 40, BLACK);
                const Rectangle resume_game_button = {
                    static_cast<float>(config.GameMapWidth) / 2 - 100,
                    static_cast<float>(config.GameMapHeight) / 2 - 50,
                    200,
                    50
                };
                if (GuiButton(resume_game_button, "#131#Resume game")) {
                    Resume();
                }
            break;
        }

        case GameState::WON: {
            DrawWinScreen();
            break;
        }

        case GameState::LOST: {
            DrawLoseScreen();
            break;
        }
    }


}

void Game::DrawWinScreen() {
    const auto& config = ApplicationConfig::GetInstance();
    ClearBackground(RAYWHITE);
    ShowCursor();
    DrawText("You won!", config.WindowRoot + 300, config.WindowRoot + 300, config.font_size, BLACK);
    DrawText("Press r to restart", config.WindowRoot + 300, config.WindowRoot + 350, config.font_size, SKYBLUE);

    if (IsKeyDown(KEY_R)) {
        Initialize(last_played_map_number_);
    }
    const Rectangle back_to_menu_button = {
        static_cast<float>(config.GameMapWidth) / 2 - 100,
        static_cast<float>(config.GameMapHeight) / 2 - 50,
        200,
        50
    };
    if (GuiButton(back_to_menu_button, "#185#Back to Menu")) {
        Stop();
    }

}

void Game::DrawLoseScreen() {
    const auto& config = ApplicationConfig::GetInstance();
    ShowCursor();
    ClearBackground(RAYWHITE);
    DrawText(std::format("You lost. Your Score was {}/{}", game_map.GetExploredTileCount(),game_map.GetFreeTileCount()).c_str(), 100, 100, config.font_size, BLACK);
    DrawText("Press r to restart", config.WindowRoot + 300, config.WindowRoot + 300, config.font_size, SKYBLUE);


    if (IsKeyDown(KEY_R)) {
        Initialize(last_played_map_number_);
    }
    const Rectangle back_to_menu_button = {
        static_cast<float>(config.GameMapWidth) / 2 - 100,
        static_cast<float>(config.GameMapHeight) / 2 - 50,
        200,
        50
    };
    if (GuiButton(back_to_menu_button, "#185#Back to Menu")) {
    Stop();
    }

}

bool Game::HasStarted() const {
    return is_game_running_;
}
