//
// Created by simon on 08.03.26.
//

#ifndef PACMAN_CPP_ENEMYPLAYER_H
#define PACMAN_CPP_ENEMYPLAYER_H
#include <queue>
#include <raylib.h>

#include "../PlayerBase.h"
#include "../HumanPlayer/HumanPlayer.h"

class EnemyPlayer : public PlayerBase {
    public:
    explicit EnemyPlayer(Map *map, Time *time, HumanPlayer *player, int starting_tile, Color color);
    void Draw() const override;
    void Move() override;

    private:
    void CheckSurroundingTiles(int tile, Direction direction);

    void BreadthFirstSearch();

    HumanPlayer *player_;
    std::vector<int> explored_set_;
    std::queue<std::pair<int, Direction>> to_be_explored_;
    std::vector<int> surrounding_tiles_;
    int last_known_player_tile_{};
};


#endif //PACMAN_CPP_ENEMYPLAYER_H