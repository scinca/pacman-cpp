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
    getTile();
    printf("INIT: posX=%.1f posY=%.1f tile=%d\n", positionX, positionY, currentTile);
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
    DrawText(TextFormat("tile:%d tileX:%d tileY:%d up_tile:%c up_valid:%d",
    tile, tileX, tileY,
    map->getTile(tileX, tileY - 1),
    map->canMove(tile - 50)), 10, 10, 20, WHITE);
    }



bool PlayerBase::checkMoveValidity(const Direction move) {
    if (std::ranges::contains(possibleMoves, move)) {
        return true;
    }
    return false;
}



PlayerBase::~PlayerBase() = default;