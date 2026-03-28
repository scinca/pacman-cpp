//
// Created by simon on 14.03.26.
//

#include "Game.h"

#include "Game.h"
#include "../config.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <raygui.h>
#include <raylib.h>


Game::Game(Database *db) : db_(db), state(GameState::PLAYING), game_map(db_) {
}

Game::~Game() = default;

void Game::Initialize(const std::optional<int> map_number) {
    HideCursor();
    enemy_players.clear();
    is_game_running_ = true;
   if (map_number.has_value()) {
       game_map.LoadMapFromDB(map_number.value());
   }
    else {
        game_map.LoadMapFromDB(last_played_map_number_);
    }




    // Find starting positions
    const int player_starting_position = game_map.FindPlayerStartTile();
    const std::vector<int> enemy_starting_positions = game_map.FindEnemyStartTiles();


    player = std::make_unique<HumanPlayer>(&game_map, &time, player_starting_position, YELLOW);

    for (int i = 0; i < enemy_starting_positions.size(); i++) {
        enemy_players.push_back(std::make_unique<EnemyPlayer>(&game_map, &time, player.get(), enemy_starting_positions[i], enemy_colors[i]));
    }


    state = GameState::PLAYING;
}

void Game::HandlePlayerInput() {
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
    time.CalculateDeltaTime();

    if (state == GameState::PLAYING) {

        if (game_map.AllExplored()) {
            state = GameState::WON;
        }
        else if (!player->CheckIfAlive()) {
            state = GameState::LOST;
        }
        else {
            // Update game entities
            player->Move();
           for (const auto& enemy : enemy_players) {
               enemy->Move();
           }
        }
    }
}


void Game::Pause() {
    state = GameState::PAUSED;
}
void Game::Resume() {
    state = GameState::PLAYING;
}

void Game::DrawFrame() {

    switch (state) {
        case GameState::PLAYING: {
            ClearBackground(BLACK);
            DrawRectangleLines(1, 1, WindowConfig::WindowWidth - 1, WindowConfig::WindowHeight - 1, RAYWHITE);
            game_map.Draw();
            player->Draw();
            for (const auto& enemy : enemy_players) {
                enemy->Draw();
            }
            break;
        }

        case GameState::PAUSED: {
            ClearBackground(RAYWHITE);
            ShowCursor();
            DrawText("Game is paused, click P to restart", 100, 100, 40, BLACK);
            constexpr Rectangle resume_game_button = {
                static_cast<float>(WindowConfig::WindowWidth / 2 - 100),
                static_cast<float>(WindowConfig::WindowHeight / 2 - 50),
                200,
                50
            };
            if (GuiButton(resume_game_button, "Resume game")) {
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
    ClearBackground(RAYWHITE);
    DrawText("You won!", 100, 100, 40, BLACK);
}

void Game::DrawLoseScreen() {
    ClearBackground(RAYWHITE);
    DrawText("You lost.", 100, 100, 40, BLACK);
    DrawText("Press r to restart", 300, 300, 40, SKYBLUE);

    if (IsKeyDown(KEY_R)) {

        Initialize();


    }
}

bool Game::ShouldClose() { // currently a wrapper because I need to make the map selector ui etc first.
    return WindowShouldClose();
}

bool Game::HasStarted() const {
    return is_game_running_;
}
