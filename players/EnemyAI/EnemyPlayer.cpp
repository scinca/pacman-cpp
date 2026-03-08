//
// Created by simon on 08.03.26.
//

#include "EnemyPlayer.h"

#include <algorithm>
#include <limits>

#include "raylib.h"
#include "../../config.h"
#include "../../time/deltaTime.h"  // ← add this
#include "../../map/map.h"

EnemyPlayer::EnemyPlayer(Map *map, Time *time, HumanPlayer *player, const int starting_tile) : PlayerBase(map, time, 0) {
    player_ = player;
    std::tie(position_x_, position_y_) = Map::GetTileCenter(starting_tile);
    GetTile();

}

void EnemyPlayer::Draw() const {
    DrawCircle(
        static_cast<int>(position_x_),
        static_cast<int>(position_y_),
        TileWidth * 0.4f, YELLOW);
}

void EnemyPlayer::Move() {

    GetTile();
    if (IsAtTileCenter()) {
        CheckSurroundingTiles();
        FindBestDirection();
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
    position_x_ = std::clamp(position_x_,
    static_cast<float>(WindowConfig::WindowRoot + TileWidth / 2),
    static_cast<float>(WindowConfig::WindowRoot + 49 * TileWidth + TileWidth / 2));
        position_y_ = std::clamp(position_y_,
        static_cast<float>(WindowConfig::WindowRoot + TileWidth / 2),
        static_cast<float>(WindowConfig::WindowRoot + 27 * TileWidth + TileWidth / 2));

        auto player_tile = player_->GetCurrentTile();
        if (player_tile== current_tile_) {
            player_->Kill();
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
    int min_distance = std::numeric_limits<int>::max();
    auto best_direction = Direction::NONE;

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
    for (const auto& direction : possible_moves_) {
        if (direction == opposite) continue; // avoids reversing
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
            case Direction::NONE:
                continue;
        }

        int distance = CalculateManhattanDistance(tile);
        if (distance < min_distance) {
            min_distance = distance;
            best_direction = direction;
        }

        }
    if (best_direction != Direction::NONE) {
        current_direction_ = best_direction;
    }
}





