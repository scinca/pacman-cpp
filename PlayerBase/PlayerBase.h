//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_PLAYER_BASE_H
#define PACMAN_CPP_PLAYER_BASE_H
#include <raylib.h>
#include <vector>
class Map;
class Time; // forward declaration because linker complains if I include header. Might investigate later.

enum class Direction {
    UP,DOWN,LEFT,RIGHT, NONE
};


class PlayerBase {
    public:
    virtual ~PlayerBase();

    PlayerBase(Map *game_map, Time *time, int tile, Color color);

    [[nodiscard]] int GetCurrentTile() const { return current_tile_; }
    virtual void Move() = 0;
    virtual void Draw() const =0;
    void ResetPosition();
    [[nodiscard]] virtual bool IsAtTileCenter();

    protected:
    bool CheckMoveValidity(Direction move);
    void GetTile();
    [[nodiscard]] int GetPreviousTile() const;


    void CheckSurroundingTiles();


    double position_x_;
    double position_y_;
    int current_tile_;
    int start_tile_;
    Color color_;
    Direction current_direction_ = Direction::NONE;
    std::vector<Direction> possible_moves_;
    Map *map_ = nullptr;
    Time *time_ = nullptr;

};



#endif //PACMAN_CPP_PLAYER_BASE_H