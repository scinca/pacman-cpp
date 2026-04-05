//
// Created by simon on 29.03.26.
//

#ifndef PACMAN_CPP_MAPCREATOR_H
#define PACMAN_CPP_MAPCREATOR_H

#include<string>
#include<optional>
#include <raylib.h>
#include <cstdint>
#include "Database/Database.h"
#include "Map/Map.h"
#include "Game/Game.h"



enum class Tile {
    Coin,
    Wall,
    PlayerStart,
    EnemyStart,
    None
};
enum class SaveDialogState {
    Hidden,
    Form,
    Success,
    Error
};


class MapCreator {
    public:
    explicit MapCreator(Database *database, Game *game);
    void DrawFrame();
    void DrawToolBox();

    void Activate();

    void HandlePlayerInput();
    void Initialize();
    static void DrawGrid();

    void ShowSaveMapDialog();
    bool MapCreated();

    bool MapValidationErrorPopup(MapValidationError error);

    void SetCurrentTool(const Tile tool){current_tool_ = tool;}
    [[nodiscard]] bool IsActive() const{return is_active_;}

private:
    void ShowClearMapConfirmationDialog();

    static Rectangle DrawDialogBackground();

    Game *game_;

    std::int64_t saved_map_id_ = 0;
    Map map_class_;
    bool is_active_ = false;
    std::optional<std::string> temporarily_saved_map_ = std::nullopt;
    std::string temporary_map_;
    Database *db_{};
    Tile current_tool_ = Tile::None;
    char map_name_buffer_[64] = {};
    char map_author_buffer_[64] = {};
    bool edit_name_ = true;
    bool edit_author_ = !edit_name_;
    SaveDialogState save_dialog_state_ = SaveDialogState::Hidden;
    bool clear_map_dialog_ = false;
    bool map_created_ = false;
    std::optional<MapValidationError> test_map_error_= std::nullopt;
    std::optional<MapValidationError> save_map_error_ = std::nullopt;

};







#endif //PACMAN_CPP_MAPCREATOR_H
