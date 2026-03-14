//
// Created by simon on 14.03.26.
//

#ifndef PACMAN_CPP_GAMEMENU_H
#define PACMAN_CPP_GAMEMENU_H
class Game;

class GameMenu {
    public:
    explicit GameMenu(Game *game);
        ~GameMenu();
    void ShowMenu();
    private:
   Game* game_;

};


#endif //PACMAN_CPP_GAMEMENU_H