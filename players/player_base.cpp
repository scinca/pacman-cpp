//
// Created by simon on 06.03.26.
//

#include "player_base.h"
#include "../config.h"

PlayerBase::PlayerBase(Map *game_map)
    :positionX(WindowConfig::WindowRoot+ TileWidth/2), positionY(WindowConfig::WindowRoot + TileWidth/2), map(game_map)
{

}

void PlayerBase::getTile() {
    currentTile = ((positionY- WindowConfig::WindowRoot) / TileWidth) * 50 + ((positionX-WindowConfig::WindowRoot) / TileWidth);
}


/* WindowRoot is 0 in this "drawing"
* (0,0) ──────────── (WindowWidth, 0)
  |                      |
  |                      |
  |                      |
(0, WindowHeight) ── (WindowWidth, WindowHeight)
 */

void PlayerBase::checkSurroundingTiles() {
    possibleMoves.clear(); // reset each invocation
    // the following if statements check if the player can move in a direction
    // by checking if there is a wall (#) or if it goes past an edge.

    if (positionX > WindowConfig::WindowRoot + TileWidth && map->canMove(currentTile - 1))
        possibleMoves.push_back(Direction::LEFT);


    if (positionX < WindowConfig::WindowRoot + (50 * TileWidth) - TileWidth && map->canMove(currentTile + 1))
        possibleMoves.push_back(Direction::RIGHT);


    if (positionY > WindowConfig::WindowRoot + TileWidth && map->canMove(currentTile - 50))
        possibleMoves.push_back(Direction::UP);


    if (positionY < WindowConfig::WindowRoot + (28 * TileWidth) - TileWidth && map->canMove(currentTile + 50))
        possibleMoves.push_back(Direction::DOWN);
    }



