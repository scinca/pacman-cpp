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
    :positionX(WindowConfig::WindowRoot+ TileWidth/2), positionY(WindowConfig::WindowRoot + TileWidth/2), currentTile(0), map(game_map), time(time)

{

}

void PlayerBase::getTile() {
    const int tileX = static_cast<int>(positionX - WindowConfig::WindowRoot) / TileWidth;
    const int tileY = static_cast<int>(positionY - WindowConfig::WindowRoot) / TileWidth;
    currentTile = tileY * 50 + tileX;
}


/* WindowRoot is 0 in this "drawing"
* (0,0) ──────────── (WindowWidth, 0)
  |                      |
  |                      |
  |                      |
(0, WindowHeight) ── (WindowWidth, WindowHeight)
 */

void PlayerBase::checkSurroundingTiles() { // it's a 50x28 grid but arrays start at 0 so 49 and 27 aren't magic numbers.

    possibleMoves.clear();

    const int tileX = static_cast<int>(positionX - WindowConfig::WindowRoot) / TileWidth;
    const int tileY = static_cast<int>(positionY - WindowConfig::WindowRoot) / TileWidth;
    const int tile = tileY * 50 + tileX;

        if (tileX > 0 && map->canMove(tile - 1))
            possibleMoves.push_back(Direction::LEFT);

        if (tileX < 49 && map->canMove(tile + 1))
            possibleMoves.push_back(Direction::RIGHT);

        if (tileY > 0 && map->canMove(tile - 50))
            possibleMoves.push_back(Direction::UP);

        if (tileY < 27 && map->canMove(tile + 50))
            possibleMoves.push_back(Direction::DOWN);

    }



bool PlayerBase::checkMoveValidity(const Direction move) {
    return std::ranges::contains(possibleMoves, move);
}


bool PlayerBase::isAtTileCenter() const {
        const float tileCenterX = WindowConfig::WindowRoot + (currentTile % 50) * TileWidth + TileWidth / 2;
        const float tileCenterY = WindowConfig::WindowRoot + (currentTile / 50) * TileWidth + TileWidth / 2;
        return std::abs(positionX - tileCenterX) < margin &&
               std::abs(positionY - tileCenterY) < margin;

}

PlayerBase::~PlayerBase() = default;