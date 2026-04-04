//
// Created by simon on 07.03.26.
//

#include "HumanPlayer.h"
#include <algorithm>
#include <raylib.h>
#include "Time/DeltaTime.h"
#include "Map/Map.h"
#include "ApplicationConfig.h"

HumanPlayer::HumanPlayer(Map *map, Time *time, const int starting_tile, const Color color)
    :PlayerBase(map, time, starting_tile, color){
    std::tie(position_x_, position_y_) = Map::GetTileCenter(starting_tile);
    start_tile_ = starting_tile;
    GetTile();
    color_ = color;
}


void HumanPlayer::Move() {
    CenterPosition();
    const auto& config = ApplicationConfig::GetInstance();
    GetTile();
    if (IsAtTileCenter()) {
        CheckSurroundingTiles();

        if (CheckMoveValidity(next_direction_)) {
            current_direction_ = next_direction_;
            next_direction_ = Direction::NONE;
        }
        else if (!CheckMoveValidity(current_direction_)) {
            current_direction_ = Direction::NONE;
        }
    }

    switch (current_direction_) {
        case Direction::UP:
            position_y_ -= config.velocity_ * time_->GetDeltaTime();
            break;
        case Direction::DOWN:
            position_y_ += config.velocity_ * time_->GetDeltaTime();
            break;
        case Direction::LEFT:
            position_x_ -= config.velocity_ * time_->GetDeltaTime();
            break;
        case Direction::RIGHT:
            position_x_ += config.velocity_ * time_->GetDeltaTime();
            break;
        case Direction::NONE:
            break;
    }
    map_->Explore(current_tile_);
}

void HumanPlayer::SetNextDirection(const Direction next_direction) {
    next_direction_ = next_direction;
}

void HumanPlayer::Kill() {
    lives_--;
    if (lives_ <= 0) { // <= bc i don't have respawn logic yet
        is_alive_ = false;
    }
}

bool HumanPlayer::CheckIfAlive() const {
    return is_alive_;
}
