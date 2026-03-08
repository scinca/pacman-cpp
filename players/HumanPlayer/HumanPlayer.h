//
// Created by simon on 07.03.26.
//

#ifndef PACMAN_CPP_HUMANPLAYER_H
#define PACMAN_CPP_HUMANPLAYER_H
#include "../player_base.h"


class HumanPlayer : public PlayerBase {
    public:
    explicit HumanPlayer(Map *map, Time *time);

    void Move() override;
    void Draw() const override;
    void Kill();
    [[nodiscard]] bool CheckIfAlive() const;
    void SetNextDirection(Direction nextDirection);
    private:
    Direction next_direction_ = Direction::NONE;  // buffered input
    bool is_alive_ = true;



};


#endif //PACMAN_CPP_HUMANPLAYER_H