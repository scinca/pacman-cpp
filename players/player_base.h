//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_PLAYER_BASE_H
#define PACMAN_CPP_PLAYER_BASE_H
#include <vector>
class Map;
class Time;

enum class Direction {
    UP,DOWN,LEFT,RIGHT, NONE
};


class PlayerBase {
    public:
    virtual ~PlayerBase();

    PlayerBase(Map *game_map, Time *time);
    virtual void move(Direction requestedDirection)= 0;

    virtual void move() { move(Direction::NONE); }
    virtual void draw() const =0;

    protected:
    bool checkMoveValidity(Direction move);
    float positionX;
    float positionY;
    int currentTile;
    int velocity = 150;
    Direction currentDirection = Direction::NONE;

    void getTile();
    void checkSurroundingTiles();

    std::vector<Direction> possibleMoves;
    Map *map = nullptr;
    Time *time = nullptr;

};



#endif //PACMAN_CPP_PLAYER_BASE_H