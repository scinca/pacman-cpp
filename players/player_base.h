//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_PLAYER_BASE_H
#define PACMAN_CPP_PLAYER_BASE_H
#include <vector>
class Map;
class Time; // forward declaration because linker complains if I include header. Might investigate later.

enum class Direction {
    UP,DOWN,LEFT,RIGHT, NONE
};


class PlayerBase {
    public:
    virtual ~PlayerBase();

    PlayerBase(Map *game_map, Time *time, int tile);


    virtual void Move() = 0;
    virtual void Draw() const =0;

    protected:
    bool CheckMoveValidity(Direction move);
    float margin_ = 2.0f;

    float position_x_;
    float position_y_;
    int current_tile_;
    int velocity_ = 150;
    Direction current_direction_ = Direction::NONE;
    [[nodiscard]] bool IsAtTileCenter() const;

    void GetTile();
    void CheckSurroundingTiles();

    std::vector<Direction> possible_moves_;
    Map *map_ = nullptr;
    Time *time_ = nullptr;

};



#endif //PACMAN_CPP_PLAYER_BASE_H