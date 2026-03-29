//
// Created by simon on 07.03.26.
//

#ifndef PACMAN_CPP_HUMANPLAYER_H
#define PACMAN_CPP_HUMANPLAYER_H
#include "../PlayerBase.h"


class HumanPlayer : public PlayerBase {
    public:
    explicit HumanPlayer(Map *map, Time *time, int starting_tile, Color color);
    void Move() override;
    void Draw() const override;
    void Kill();
    [[nodiscard]] bool CheckIfAlive() const;
    void SetNextDirection(Direction next_direction);
    [[nodiscard]] std::pair<int, int> GetPosition() const;
    [[nodiscard]] int GetRemainingLives() const{return lives_;};
    int GetMaxLives() const{return max_lives_;};

    private:
    Direction next_direction_ = Direction::NONE;  // buffered input
    bool is_alive_ = true;
    int max_lives_ = 3;
    int lives_ = max_lives_;





};


#endif //PACMAN_CPP_HUMANPLAYER_H