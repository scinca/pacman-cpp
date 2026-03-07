//
// Created by simon on 07.03.26.
//

#include "HumanPlayer.h"

#include <algorithm>

#include "../../config.h"
#include <raylib.h>
#include "../../time/deltaTime.h"
#include "../../map/map.h"
/*
HumanPlayer::HumanPlayer(Map *map, Time *time)
    :PlayerBase(map, time){
}


void HumanPlayer::move(const Direction requestedDirection) {
    checkSurroundingTiles();
    if (!checkMoveValidity(requestedDirection)) {
        return;
    }
    // snap to grid when changing axis
    if (requestedDirection == Direction::LEFT || requestedDirection == Direction::RIGHT) {
        // snap Y to tile center
        positionY = (static_cast<int>(positionY - WindowConfig::WindowRoot) / TileWidth)
                    * TileWidth + TileWidth / 2 + WindowConfig::WindowRoot;
    }
    if (requestedDirection == Direction::UP || requestedDirection == Direction::DOWN) {
        // snap X to tile center
        positionX = (static_cast<int>(positionX - WindowConfig::WindowRoot) / TileWidth)
                    * TileWidth + TileWidth / 2 + WindowConfig::WindowRoot;
    }
    currentDirection = requestedDirection;
    switch (currentDirection) {
        case Direction::UP:
            positionY -= static_cast<int>(velocity * time->getDeltaTime());
            break;
        case Direction::DOWN:
            positionY += (velocity * time->getDeltaTime());
            break;
        case Direction::LEFT:
            positionX -= static_cast<int>(velocity * time->getDeltaTime());
            break;
        case Direction::RIGHT:
            positionX += static_cast<int>(velocity * time->getDeltaTime());
            break;
        case Direction::NONE:
            break;
    }
    getTile();
    map->explore(currentTile);
}

void HumanPlayer::move() {
    move(currentDirection);
}
void HumanPlayer::draw() const  {
    DrawCircle(positionX, positionY, TileWidth* 0.4, RED);
}
*/
HumanPlayer::HumanPlayer(Map *map, Time *time)
    :PlayerBase(map, time){
}


void HumanPlayer::move(const Direction requestedDirection) {
    checkSurroundingTiles();

    if (!checkMoveValidity(requestedDirection)) {
        return;
    }

    // snap to grid when changing axis
    if (requestedDirection == Direction::LEFT || requestedDirection == Direction::RIGHT) {
        positionY = (static_cast<int>(positionY - WindowConfig::WindowRoot) / TileWidth)
                    * TileWidth + TileWidth / 2 + WindowConfig::WindowRoot;
    }
    if (requestedDirection == Direction::UP || requestedDirection == Direction::DOWN) {
        positionX = (static_cast<int>(positionX - WindowConfig::WindowRoot) / TileWidth)
                    * TileWidth + TileWidth / 2 + WindowConfig::WindowRoot;
    }

    currentDirection = requestedDirection;

    switch (currentDirection) {
        case Direction::UP:
            positionY -= velocity * time->getDeltaTime();
            break;
        case Direction::DOWN:
            positionY += velocity * time->getDeltaTime();
            break;
        case Direction::LEFT:
            positionX -= velocity * time->getDeltaTime();
            break;
        case Direction::RIGHT:
            positionX += velocity * time->getDeltaTime();
            break;
        case Direction::NONE:
            break;
    }

    // snap perpendicular axis to tile center while moving
    const int newTileX = static_cast<int>(positionX - WindowConfig::WindowRoot) / TileWidth;
    const int newTileY = static_cast<int>(positionY - WindowConfig::WindowRoot) / TileWidth;

    if (currentDirection == Direction::UP || currentDirection == Direction::DOWN) {
        positionX = WindowConfig::WindowRoot + newTileX * TileWidth + TileWidth / 2;
    }
    if (currentDirection == Direction::LEFT || currentDirection == Direction::RIGHT) {
        positionY = WindowConfig::WindowRoot + newTileY * TileWidth + TileWidth / 2;
    }

    getTile();
    const int tileX = currentTile % 50;
    const int tileY = currentTile / 50;
    bool nextBlocked = false;
    if (currentDirection == Direction::UP)    nextBlocked = !map->canMove(currentTile - 50);
    if (currentDirection == Direction::DOWN)  nextBlocked = !map->canMove(currentTile + 50);
    if (currentDirection == Direction::LEFT)  nextBlocked = !map->canMove(currentTile - 1);
    if (currentDirection == Direction::RIGHT) nextBlocked = !map->canMove(currentTile + 1);

    if (nextBlocked) {
        // snap to current tile center
        positionX = WindowConfig::WindowRoot + tileX * TileWidth + TileWidth / 2;
        positionY = WindowConfig::WindowRoot + tileY * TileWidth + TileWidth / 2;
    }
    map->explore(currentTile);
}

void HumanPlayer::move() {
    move(currentDirection);
}

void HumanPlayer::draw() const {
    DrawCircle(positionX, positionY, TileWidth * 0.4f, RED);
}