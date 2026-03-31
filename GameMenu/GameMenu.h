//
// Created by simon on 14.03.26.
//

#ifndef PACMAN_CPP_GAMEMENU_H
#define PACMAN_CPP_GAMEMENU_H

#include "Game/Game.h"
#include "MapCreator/MapCreator.h"
class GameMenu {
public:
    explicit GameMenu(Game *game, MapCreator *map_creator, Database* db);
    ~GameMenu();
    void Show() const;

    void DrawMapInfo(const MapInfo &data, int i) const;

private:
   Game* game_;
   MapCreator* map_creator_;
   Database* db_;
   std::vector <MapInfo> maps;

};


#endif //PACMAN_CPP_GAMEMENU_H