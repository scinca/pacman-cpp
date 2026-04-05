//
// Created by simon on 06.03.26.
//

#include "PlayerBase.h"

#include <algorithm>
#include <raylib.h>
#include "ApplicationConfig.h"
#include "Map/Map.h"

PlayerBase::PlayerBase(Map *game_map, Time *time, const int tile, const Color color)
    :position_x_(static_cast<float>(ApplicationConfig::GetInstance().GameMapRootX) + ApplicationConfig::GetInstance().TileWidth /2),
    position_y_(static_cast<float>(ApplicationConfig::GetInstance().GameMapRootY) + ApplicationConfig::GetInstance().TileWidth/2),
    current_tile_(tile), color_(color), map_(game_map), time_(time)
{}

PlayerBase::~PlayerBase() = default;

void PlayerBase::Draw() const {
    const auto& config = ApplicationConfig::GetInstance();
    DrawCircle(
        static_cast<int>(position_x_),
        static_cast<int>(position_y_),
        config.TileWidth * 0.4f, color_);
}

void PlayerBase::GetTile() {
    const auto& config = ApplicationConfig::GetInstance();

    const int tile_x = ( static_cast<int>(position_x_) - config.GameMapRootX) / static_cast<int>(config.TileWidth);
    const int tile_y = (static_cast<int>(position_y_) -  config.GameMapRootY) /  static_cast<int>(config.TileWidth);
    current_tile_ = tile_y * config.TilesX + tile_x;
}


/* WindowRoot is 0 in this "drawing"
* (0,0) ──────────── (WindowWidth, 0)
  |                      |
  |                      |
  |                      |
(0, WindowHeight) ── (WindowWidth, WindowHeight)
 */

void PlayerBase::CheckSurroundingTiles() {
    const auto& config = ApplicationConfig::GetInstance();
    possible_moves_.clear();

    const int tile_x = ( static_cast<int>(position_x_) - config.GameMapRootX) / static_cast<int>(config.TileWidth);
    const int tile_y = (static_cast<int>(position_y_) -  config.GameMapRootY) /  static_cast<int>(config.TileWidth);
    const int tile = tile_y * config.TilesX + tile_x;


        if (tile_x > 0 && map_->CanMove(tile - 1)) {
            possible_moves_.push_back(Direction::LEFT);
        }
        if (tile_x < config.TilesX-1 && map_->CanMove(tile + 1)) {
            possible_moves_.push_back(Direction::RIGHT);
        }
        if (tile_y > 0 && map_->CanMove(tile - config.TilesX)) {
            possible_moves_.push_back(Direction::UP);
        }
        if (tile_y < config.TilesY -1 && map_->CanMove(tile + config.TilesX)) {
            possible_moves_.push_back(Direction::DOWN);
        }
}


void PlayerBase::CenterPosition() {
    auto [center_x, center_y] = Map::GetTileCenter(current_tile_);
    switch (current_direction_) {
        //the fallthrough is intentional so that my IDE doesn't give a warning for consecutive identical branches
        case Direction::UP:
        case Direction::DOWN:
            if (position_x_ > center_x) {
                position_x_--;
            }
            if (position_x_ < center_x) {
                position_x_++;
            }
            break;
        case Direction::LEFT:
        case Direction::RIGHT:
            if (position_y_ > center_y) {
                position_y_--;
            }
            if (position_y_ < center_y) {
                position_y_++;
            }
            break;
        case Direction::NONE:
            break;
    }
}

bool PlayerBase::CheckMoveValidity(const Direction move) {
    return std::ranges::contains(possible_moves_, move);
}

bool PlayerBase::IsAtTileCenter() const {
    const auto& config = ApplicationConfig::GetInstance();
    auto [tile_center_x, tile_center_y] = Map::GetTileCenter(current_tile_);
    return std::abs(position_x_ - tile_center_x) < config.margin_ &&
           std::abs(position_y_ - tile_center_y) < config.margin_;
}


void PlayerBase::UpdatePosition() {
    const auto& config = ApplicationConfig::GetInstance();

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
}


void PlayerBase::ResetPosition() {
    current_tile_ = start_tile_;
    std::tie(position_x_, position_y_) = Map::GetTileCenter(current_tile_);
}
