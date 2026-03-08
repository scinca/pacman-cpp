//
// Created by simon on 08.03.26.
//

#ifndef PACMAN_CPP_ENEMYPLAYER_H
#define PACMAN_CPP_ENEMYPLAYER_H
#include "../player_base.h"
#include "../HumanPlayer/HumanPlayer.h"

class EnemyPlayer : public PlayerBase {
    public:
    explicit EnemyPlayer(Map *map, Time *time, HumanPlayer *player, int starting_tile);
    void Draw() const override;
    void Move() override;

    private:
    HumanPlayer *player_;
    std::vector<int> surrounding_tiles_;
    [[nodiscard]] int CalculateManhattanDistance(int tile) const;
    void FindBestDirection();
};


#endif //PACMAN_CPP_ENEMYPLAYER_H