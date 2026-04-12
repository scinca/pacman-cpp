//
// Created by simon on 07.03.26.
//

#include "HumanPlayer.h"
#include <raylib.h>
#include <stdexcept>
#include <utility>
#include <optional>
#include "Time/DeltaTime.h"
#include "Map/Map.h"

HumanPlayer::HumanPlayer(Map *map, Time *time, const int starting_tile, const Color color)
    :PlayerBase(map, time, starting_tile, color){
    const auto temp_positions = Map::GetTileCenter(starting_tile);
    if (temp_positions.has_value()) {
        std::tie(position_x_, position_y_) = temp_positions.value();
    }else {
        throw std::runtime_error("starting position invalid ( This shouldn't have happened since Map should have been validated");
    }
    start_tile_ = starting_tile;
    GetTile();
    color_ = color;
}


void HumanPlayer::Move() {
    GetTile();
    CenterPosition();

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

    UpdatePosition();
    map_->Explore(current_tile_);
}

void HumanPlayer::SetNextDirection(const Direction next_direction) {
    next_direction_ = next_direction;
}

void HumanPlayer::Kill() {
    lives_--;
    if (lives_ <= 0) {
        is_alive_ = false;
    }
}

bool HumanPlayer::CheckIfAlive() const {
    return is_alive_;
}
