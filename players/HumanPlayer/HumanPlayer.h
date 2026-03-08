//
// Created by simon on 07.03.26.
//

#ifndef PACMAN_CPP_HUMANPLAYER_H
#define PACMAN_CPP_HUMANPLAYER_H
#include "../player_base.h"


class HumanPlayer : public PlayerBase {
    public:
    explicit HumanPlayer(Map *map, Time *time);
    void move(Direction requestedDirection) override;
    void move() override;
    void draw() const override;

    void setNextDirection(Direction nextDirection);
    private:
    Direction m_nextDirection = Direction::NONE;  // buffered input


};


#endif //PACMAN_CPP_HUMANPLAYER_H