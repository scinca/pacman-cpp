//
// Created by simon on 29.03.26.
//

#ifndef PACMAN_CPP_MAPCREATOR_H
#define PACMAN_CPP_MAPCREATOR_H
#include <vector>

#include "../Database/Database.h"
#include "../Map/Map.h"


class MapCreator {
    public:
    explicit MapCreator(Database *database);

    void DrawFrame();

    void Initialize();

    void DrawGrid();

    [[nodiscard]] bool IsActive() const{return is_active_;}

private:
    Map map_class_;
    bool is_active_;
    std::string temporary_map_;
    Database *db_{};




};

enum class Tiles {
    Coin,
    Wall,
    PlayerStart,
    EnemyStart
};



#endif //PACMAN_CPP_MAPCREATOR_H
