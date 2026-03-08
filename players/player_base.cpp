//
// Created by simon on 06.03.26.
//

#include "player_base.h"

#include <algorithm>
#include <raylib.h>
#include "../config.h"
#include "../time/deltaTime.h"
#include "../map/map.h"

PlayerBase::PlayerBase(Map *game_map, Time *time)// currentTile is 0 because I will implement a system to set currentTile starting Point in the map
    :position_x_(WindowConfig::WindowRoot+ TileWidth/2), position_y_(WindowConfig::WindowRoot + TileWidth/2), current_tile_(0), map_(game_map), time_(time)

{

}

void PlayerBase::GetTile() {
    const int tileX = static_cast<int>(position_x_ - WindowConfig::WindowRoot) / TileWidth;
    const int tileY = static_cast<int>(position_y_ - WindowConfig::WindowRoot) / TileWidth;
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

    possible_moves_.clear();

    const int tile_x = static_cast<int>(position_x_ - WindowConfig::WindowRoot) / TileWidth;
    const int tile_y = static_cast<int>(position_y_ - WindowConfig::WindowRoot) / TileWidth;
    const int tile = tile_y * 50 + tile_x;

        if (tile_x > 0 && map_->CanMove(tile - 1))
            possible_moves_.push_back(Direction::LEFT);

        if (tile_x < 49 && map_->CanMove(tile + 1))
            possible_moves_.push_back(Direction::RIGHT);

        if (tile_y > 0 && map_->CanMove(tile - 50))
            possible_moves_.push_back(Direction::UP);

        if (tile_y < 27 && map_->CanMove(tile + 50))
            possible_moves_.push_back(Direction::DOWN);

    }



bool PlayerBase::CheckMoveValidity(const Direction move) {
    return std::ranges::contains(possible_moves_, move);
}


bool PlayerBase::IsAtTileCenter() const {
        const float tile_center_x = WindowConfig::WindowRoot + (current_tile_ % 50) * TileWidth + TileWidth / 2;
        const float tile_center_y = WindowConfig::WindowRoot + (current_tile_ / 50) * TileWidth + TileWidth / 2;
        return std::abs(position_x_ - tile_center_x) < margin_ &&
               std::abs(position_y_ - tile_center_y) < margin_;

}

PlayerBase::~PlayerBase() = default;