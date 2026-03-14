//
// Created by simon on 14.03.26.
//

#include "Game.h"

#include "Game.h"
#include "../config.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Game::Game() : state(GameState::PLAYING) {
}

Game::~Game() {

}

void Game::Initialize(const std::optional<std::string> &map_path) {
    is_game_running_ = true;
    if (!map_path.has_value()) {
        game_map.LoadDefaultMap();
    }
    else {
        auto loading_result = game_map.Load(map_path.value());
        if (!loading_result) {
            const std::string_view loading_error = loading_result.error();
            std::cerr << "Failed to load map: " << loading_error << "\n";
            game_map.LoadDefaultMap();
        }
    }


    // Find starting positions
    const int player_starting_position = game_map.FindPlayerStartTile();
    const std::vector<int> enemy_starting_positions = game_map.FindEnemyStartTiles();

    // create players NEEDS TO BE REDONE LATER via vector
    player = std::make_unique<HumanPlayer>(&game_map, &time, player_starting_position, YELLOW);
    red_enemy = std::make_unique<EnemyPlayer>(&game_map, &time, player.get(), enemy_starting_positions[0], RED);
    blue_enemy = std::make_unique<EnemyPlayer>(&game_map, &time, player.get(), enemy_starting_positions[1], SKYBLUE);

    state = GameState::PLAYING;
}

void Game::ProcessInput() const {
    if (state != GameState::PLAYING) {
        return;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
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
            red_enemy->Move();
            blue_enemy->Move();
        }
    }
}

void Game::DrawFrame() {

    switch (state) {
        case GameState::PLAYING:
            ClearBackground(BLACK);
            DrawRectangleLines(1, 1, WindowConfig::WindowWidth - 1, WindowConfig::WindowHeight - 1, RAYWHITE);
            game_map.Draw();
            player->Draw();
            red_enemy->Draw();
            blue_enemy->Draw();
            break;

        case GameState::WON:
            DrawWinScreen();
            break;

        case GameState::LOST:
            DrawLoseScreen();
            break;
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

        is_game_running_ = false;


    }
}

bool Game::ShouldClose() { // currently a wrapper because I need to make the map selector ui etc first.
    return WindowShouldClose();
}

bool Game::HasStarted() const {
    return is_game_running_;
}
