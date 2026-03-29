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
    void DrawToolBox();
    void HandlePlayerInput();
    void Initialize();
    static void DrawGrid();

    void SaveMapDialog();

    void SetCurrentTool(const Tile tool){current_tool_ = tool;}
    [[nodiscard]] bool IsActive() const{return is_active_;}

private:
    Map map_class_;
    bool is_active_;
    std::string temporary_map_;
    Database *db_{};
    Tile current_tool_ = Tile::None;
    bool show_save_dialog_ = false;
    char map_name_buffer_[64] = {};
    char map_author_buffer_[64] = {};
    bool edit_name_ = true;
    bool edit_author_ = !edit_name_;





};







#endif //PACMAN_CPP_MAPCREATOR_H
