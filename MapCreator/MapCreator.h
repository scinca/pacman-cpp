//
// Created by simon on 29.03.26.
//

#ifndef PACMAN_CPP_MAPCREATOR_H
#define PACMAN_CPP_MAPCREATOR_H
#include <vector>

#include "../Database/Database.h"


class MapCreator {
    public:
    explicit MapCreator(Database *database);

    private:
    std::vector<char>temporary_map_;
    Database *db_{};



};



#endif //PACMAN_CPP_MAPCREATOR_H
