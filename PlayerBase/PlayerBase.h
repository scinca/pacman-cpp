//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_PLAYER_BASE_H
#define PACMAN_CPP_PLAYER_BASE_H
#include <raylib.h>
#include <vector>
#include "Map/Map.h"
#include "Time/DeltaTime.h"

enum class Direction {
    UP,DOWN,LEFT,RIGHT, NONE
};


class PlayerBase {
    public:
    virtual ~PlayerBase();
    PlayerBase(Map *game_map, Time *time, int tile, Color color);
    virtual void Move() = 0;
    [[nodiscard]] int GetCurrentTile() const { return current_tile_; }
    void GetTile(); // one is used by player itself one by enemy
    void Draw() const;
    void ResetPosition();
    [[nodiscard]] bool IsAtTileCenter() const;
    void CenterPosition();

    protected:
    void UpdatePosition();
    void CheckSurroundingTiles();
    bool CheckMoveValidity(Direction move);


    float position_x_;
    float position_y_;
    int current_tile_;
    int start_tile_{};
    Color color_;
    Direction current_direction_ = Direction::NONE;
    std::vector<Direction> possible_moves_;
    Map *map_;
    Time *time_;

};



#endif //PACMAN_CPP_PLAYER_BASE_H