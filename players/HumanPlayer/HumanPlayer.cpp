//
// Created by simon on 07.03.26.
//

#include "HumanPlayer.h"

#include <algorithm>

#include "../../config.h"
#include <raylib.h>
#include "../../time/deltaTime.h"
#include "../../map/map.h"

HumanPlayer::HumanPlayer(Map *map, Time *time)
    :PlayerBase(map, time){
}


void HumanPlayer::move(const Direction requestedDirection) {
    getTile();
    if (isAtTileCenter()) {
        checkSurroundingTiles();
        if (checkMoveValidity(requestedDirection)) {
            currentDirection = requestedDirection;
        }
        // stop if current direction is now blocked
        if (!checkMoveValidity(currentDirection)) {
            currentDirection = Direction::NONE;
        }
    }



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
        getTile();
        map->explore(currentTile);

}



void HumanPlayer::move() {
    getTile();
    if (isAtTileCenter()) {
        checkSurroundingTiles();

        if (checkMoveValidity(m_nextDirection)) { //try buffered input.
            currentDirection = m_nextDirection;
            m_nextDirection = Direction::NONE;
        }
        // stop if current direction is now blocked
        if (!checkMoveValidity(currentDirection)) {
            currentDirection = Direction::NONE;
        }

    }
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
    getTile();
    map->explore(currentTile);

}



void HumanPlayer::draw() const {
    DrawCircle(
        static_cast<int>(positionX),
        static_cast<int>(positionY),
        TileWidth * 0.4f, RED);
}

void HumanPlayer::setNextDirection(Direction nextDirection) {
    m_nextDirection = nextDirection;

}