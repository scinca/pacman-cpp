//
// Created by simon on 29.03.26.
//

#ifndef PACMAN_CPP_MAPCREATOR_H
#define PACMAN_CPP_MAPCREATOR_H
#include <vector>

#include "../Database/Database.h"
#include "../Map/Map.h"

enum class Tile {
    Coin,
    Wall,
    PlayerStart,
    EnemyStart,
    None
};

class MapCreator {
    public:
    explicit MapCreator(Database *database);

    void DrawFrame();

    void Update();

    void DrawToolBox();

    void HandlePlayerInput();

    void Initialize();

    static void DrawGrid();
    void SetCurrentTool(const Tile tile){current_tile_ = tile;}
    [[nodiscard]] Tile GetCurrentTile() const {return current_tile_;}

    [[nodiscard]] bool IsActive() const{return is_active_;}

private:
    Map map_class_;
    bool is_active_;
    std::string temporary_map_;
    Database *db_{};
    Tile current_tile_ = Tile::None;




};







#endif //PACMAN_CPP_MAPCREATOR_H
