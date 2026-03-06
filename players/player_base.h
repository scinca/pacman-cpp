//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_PLAYER_BASE_H
#define PACMAN_CPP_PLAYER_BASE_H
#include <vector>

#include "../map/map.h"

enum class Direction {
    UP,DOWN,LEFT,RIGHT, NONE
};


class PlayerBase {
    public:
    PlayerBase(Map *game_map);

    protected:
    int positionX;
    int positionY;
    int currentTile;
    Direction currentDirection = Direction::NONE;

    void getTile();
    void checkSurroundingTiles();

    std::vector<Direction> possibleMoves;
    Map *map = nullptr;

};



#endif //PACMAN_CPP_PLAYER_BASE_H