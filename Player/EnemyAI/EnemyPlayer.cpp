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

int EnemyPlayer::CalculateManhattanDistance(const int tile) const {
    const int tile_x = tile % 50;
    const int tile_y = tile / 50;
    const int player_tile = player_->GetCurrentTile();
    const int player_tile_x = player_tile % 50;
    const int player_tile_y = player_tile / 50;
    return std::abs(tile_x - player_tile_x) + std::abs(tile_y - player_tile_y);
}


void EnemyPlayer::FindBestDirection() {
    const auto& config = ApplicationConfig::GetInstance();
    auto opposite = Direction::NONE;
    if (current_direction_ == Direction::UP) {
        opposite = Direction::DOWN;
    }
    if (current_direction_ == Direction::DOWN) {
        opposite = Direction::UP;
    }
    if (current_direction_ == Direction::LEFT) {
        opposite = Direction::RIGHT;
    }
    if (current_direction_ == Direction::RIGHT) {
        opposite = Direction::LEFT;
    }

    if (GetRandomValue(0, 100) < config.failure_percentage) { // 15% chance of random move so that the gameplay doesn't feel repetitive.
       current_direction_ = possible_moves_.at(GetRandomValue(0, possible_moves_.size() - 1));
    }

    int min_distance = std::numeric_limits<int>::max();
    auto best_direction = Direction::NONE;

    for (const auto& direction : possible_moves_) {
        if (direction == opposite && possible_moves_.size() > 2) {
            continue;
        }
        int tile = -1;
        switch (direction) {
            case Direction::UP:
                tile = current_tile_ - 50; break;
            case Direction::DOWN:
                tile = current_tile_ + 50; break;
            case Direction::LEFT:
                tile = current_tile_ - 1;  break;
            case Direction::RIGHT:
                tile = current_tile_ + 1;  break;
            case Direction::NONE:  continue;
        }
        int distance = CalculateManhattanDistance(tile);
        if (distance < min_distance) {
            min_distance = distance;
            best_direction = direction;
        }
    }

    if (best_direction != Direction::NONE) { // sanity check
        current_direction_ = best_direction;
    }
}

void EnemyPlayer::CheckSurroundingTiles(const int tile, Direction direction) {
    const auto& config = ApplicationConfig::GetInstance();
    if (tile > config.TilesX * config.TilesY) {
        return;
    }

    auto [tile_x, tile_y] = Map::GetTileCenter(tile);
    if (tile_x < 0 || tile_y< 0) {
        return;
    }
    if (tile_x > 0 && map_->CanMove(tile - 1)) {
        if (direction == Direction::NONE) {
            direction = Direction::LEFT;
        }
        to_be_explored_.emplace(tile -1,direction);
    }
    if (tile_x < config.TilesX-1 && map_->CanMove(tile + 1)) {
        if (direction == Direction::NONE) {
            direction = Direction::RIGHT;
        }
        to_be_explored_.emplace(  tile+1 ,direction);
    }
    if (tile_y > 0 && map_->CanMove(tile - config.TilesX)) {
        if (direction == Direction::NONE) {
            direction = Direction::UP;
        }
        to_be_explored_.emplace(tile - config.TilesX,direction);
    }
    if (tile_y < config.TilesY -1 && map_->CanMove(tile + config.TilesX)) {
        if (direction == Direction::NONE) {
            direction = Direction::DOWN;
        }
        to_be_explored_.emplace(tile + config.TilesX,direction);
    }
}



void EnemyPlayer::BreadthFirstSearch() {
    std::queue<std::pair<int, Direction>> empty_queue;
    std::vector<int>explored_set;
    to_be_explored_.swap(empty_queue);

    auto target_dir = Direction::NONE;
    to_be_explored_.emplace(current_tile_, target_dir);
    while (!to_be_explored_.empty()) {

        auto [tile , Direction] = to_be_explored_.front();
        if (tile == player_->GetCurrentTile()) {
            current_direction_ = target_dir;
        }
        if (std::ranges::find(explored_set, tile) == end(explored_set)) {
            CheckSurroundingTiles(tile, Direction);
            explored_set.push_back(tile);
        }
        to_be_explored_.pop();
    }
}


