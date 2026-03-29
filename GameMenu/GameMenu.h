//
// Created by simon on 14.03.26.
//

#ifndef PACMAN_CPP_GAMEMENU_H
#define PACMAN_CPP_GAMEMENU_H

#include "../Game/Game.h"
#include "../MapCreator/MapCreator.h"
class GameMenu {
public:
    explicit GameMenu(Game *game, MapCreator *map_creator);
    ~GameMenu();
    void Show() const;

private:
   Game* game_;
    MapCreator* map_creator_;

};


#endif //PACMAN_CPP_GAMEMENU_H