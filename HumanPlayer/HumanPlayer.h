//
// Created by simon on 07.03.26.
//

#ifndef PACMAN_CPP_HUMANPLAYER_H
#define PACMAN_CPP_HUMANPLAYER_H
#include "PlayerBase/PlayerBase.h"


class HumanPlayer : public PlayerBase {
    public:
    explicit HumanPlayer(Map *map, Time *time, int starting_tile, Color color);
    void Move() override;
    void Kill();
    [[nodiscard]] bool CheckIfAlive() const;
    void SetNextDirection(Direction next_direction);
    [[nodiscard]] int GetRemainingLives() const{return lives_;};
    [[nodiscard]] int GetMaxLives() const{return max_lives_;};

    private:
    Direction next_direction_ = Direction::NONE;  // buffered input
    bool is_alive_ = true;
    int max_lives_ = 3;
    int lives_ = max_lives_;





};


#endif //PACMAN_CPP_HUMANPLAYER_H