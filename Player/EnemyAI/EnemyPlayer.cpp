//
// Created by simon on 08.03.26.
//

#include "EnemyPlayer.h"

#include <algorithm>
#include <limits>

#include "raylib.h"
#include "ApplicationConfig.h"
#include "time/deltaTime.h"
#include "Map/Map.h"

EnemyPlayer::EnemyPlayer(Map *map, Time *time, HumanPlayer *player, const int starting_tile, const Color color) : PlayerBase(map, time, starting_tile, color) {
    player_ = player;
    color_ = color;
    std::tie(position_x_, position_y_) = Map::GetTileCenter(starting_tile);
    start_tile_ = starting_tile;
    GetTile();
    last_known_player_tile_ = player_->GetCurrentTile();

}

void EnemyPlayer::Draw() const {
    const auto& config = ApplicationConfig::GetInstance();
    DrawCircle(
        static_cast<int>(position_x_),
        static_cast<int>(position_y_),
        config.TileWidth * 0.4f, color_);
}

void EnemyPlayer::Move() {

    GetTile();

    TraceLog(LOG_INFO, "tile: %d, atCenter: %d, playerTile: %d, lastKnown: %d",
       current_tile_, IsAtTileCenter(), player_->GetCurrentTile(), last_known_player_tile_);

    if (IsAtTileCenter() || player_->GetCurrentTile() != last_known_player_tile_) {
        BreadthFirstSearch();
        }

    switch (current_direction_) {
        case Direction::UP:
            position_y_ -= velocity_ * time_->GetDeltaTime();
            break;
        case Direction::DOWN:
            position_y_ += velocity_ * time_->GetDeltaTime();
            break;
        case Direction::LEFT:
            position_x_ -= velocity_ * time_->GetDeltaTime();
            break;
        case Direction::RIGHT:
            position_x_ += velocity_ * time_->GetDeltaTime();
            break;
        case Direction::NONE:
            break;

    }
}

void EnemyPlayer::CheckSurroundingTiles(const int tile, const Direction direction) {
    const auto& config = ApplicationConfig::GetInstance();
    if (tile > config.TilesX * config.TilesY) {
        return;
    }

    auto [tile_x, tile_y] = Map::GetTileCenter(tile);
    if (tile_x < 0 || tile_y< 0) {
        return;
    }
    if (tile_x > 0 && map_->CanMove(tile - 1)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::LEFT : direction;

        to_be_explored_.emplace(tile -1,temp_direction);
    }
    if (tile_x < config.TilesX-1 && map_->CanMove(tile + 1)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::RIGHT : direction;

        to_be_explored_.emplace(  tile+1 ,temp_direction);
    }
    if (tile_y > 0 && map_->CanMove(tile - config.TilesX)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::UP : direction;

        to_be_explored_.emplace(tile - config.TilesX,temp_direction);
    }
    if (tile_y < config.TilesY -1 && map_->CanMove(tile + config.TilesX)) {
        Direction temp_direction = (direction == Direction::NONE) ? Direction::DOWN : direction;
        to_be_explored_.emplace(tile + config.TilesX,temp_direction);
    }
}



void EnemyPlayer::BreadthFirstSearch() {
    std::queue<std::pair<int, Direction>> empty_queue;
    std::vector<int>explored_set;
    to_be_explored_.swap(empty_queue);

    auto target_dir = Direction::NONE;
    to_be_explored_.emplace(current_tile_, target_dir);
    while (!to_be_explored_.empty()) {

        auto [tile , direction] = to_be_explored_.front();
        if (tile == player_->GetCurrentTile()) {
            current_direction_ = direction;
            if (player_->GetCurrentTile() != last_known_player_tile_) {
                last_known_player_tile_ = player_->GetCurrentTile();
            }
            return;
        }
        if (std::ranges::find(explored_set, tile) == end(explored_set)) {
            CheckSurroundingTiles(tile, direction);
            explored_set.push_back(tile);
        }
        to_be_explored_.pop();
    }
}


