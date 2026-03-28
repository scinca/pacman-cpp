//
// Created by simon on 06.03.26.
//

#include "PlayerBase.h"

#include <algorithm>
#include <raylib.h>
#include "../ApplicationConfig.h"
#include "../Map/Map.h"

PlayerBase::PlayerBase(Map *game_map, Time *time, const int tile, const Color color)
    :position_x_(ApplicationConfig::GetInstance().GameMapRootX+ ApplicationConfig::GetInstance().TileWidth /2), position_y_(ApplicationConfig::GetInstance().GameMapRootY + ApplicationConfig::GetInstance().TileWidth/2), current_tile_(tile), color_(color), map_(game_map), time_(time)
{

}

void PlayerBase::GetTile() {
    const auto& config = ApplicationConfig::GetInstance();

    const int tileX = static_cast<int>(position_x_ - config.GameMapRootX) / config.TileWidth;
    const int tileY = static_cast<int>(position_y_ -  config.GameMapRootY) /  config.TileWidth;
    current_tile_ = tileY * 50 + tileX;
}


/* WindowRoot is 0 in this "drawing"
* (0,0) ──────────── (WindowWidth, 0)
  |                      |
  |                      |
  |                      |
(0, WindowHeight) ── (WindowWidth, WindowHeight)
 */

void PlayerBase::CheckSurroundingTiles() { // it's a 50x28 grid but arrays start at 0 so 49 and 27 aren't magic numbers.
    const auto& config = ApplicationConfig::GetInstance();
    possible_moves_.clear();

    const int tile_x = static_cast<int>(position_x_ -config.GameMapRootX) / config.TileWidth;
    const int tile_y = static_cast<int>(position_y_ - config.GameMapRootY) / config.TileWidth;
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



bool PlayerBase::CheckMoveValidity(const Direction move) {
    return std::ranges::contains(possible_moves_, move);
}


bool PlayerBase::IsAtTileCenter() const {
    const auto& config = ApplicationConfig::GetInstance();
        const float tile_center_x = config.GameMapRootX + (current_tile_ % config.TilesX) * config.TileWidth + config.TileWidth / 2;
        const float tile_center_y = config.GameMapRootY + (current_tile_ / config.TilesX) * config.TileWidth + config.TileWidth / 2;
        return std::abs(position_x_ - tile_center_x) < margin_ &&
               std::abs(position_y_ - tile_center_y) < margin_;

}

PlayerBase::~PlayerBase() = default;