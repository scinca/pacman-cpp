//
// Created by simon on 08.03.26.
//

#include "EnemyPlayer.h"

#include <limits>

#include "raylib.h"
#include "../../config.h"
#include "../../time/deltaTime.h"  // ← add this
#include "../../map/map.h"

EnemyPlayer::EnemyPlayer(Map *map, Time *time, HumanPlayer *player, const int starting_tile) : PlayerBase(map, time, 0) {
    player_ = player;
    std::tie(position_x_, position_y_) = Map::GetTileCenter(starting_tile);


}

void EnemyPlayer::Draw() const {
    DrawCircle(
        static_cast<int>(position_x_),
        static_cast<int>(position_y_),
        TileWidth * 0.4f, YELLOW);
}

void EnemyPlayer::Move() {
    auto [player_x, player_y] = player_->GetPosition();
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
}





int EnemyPlayer::CalculateManhattanDistance(const int tile) const {


    auto [current_x, current_y] = Map::GetTileCenter(tile);
    auto [player_x, player_y] = player_->GetPosition();
    const float difference_x = std::abs(current_x - player_x);
    const float difference_y = std::abs(current_y - player_y);
    return static_cast<int>(difference_x + difference_y);

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





