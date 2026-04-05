//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

#include <algorithm>
#include <format>
#include <raygui.h>
#include <raylib.h>
#include <utility>
#include <string>

#include "ApplicationConfig.h"


MapCreator::MapCreator(Database *database, Game *game): game_(game), db_(database)
{}

void MapCreator::Activate() {
    is_active_ = true;
}

void MapCreator::DrawFrame() {
    ClearBackground(BLACK);
        DrawToolBox();
        map_class_.Draw(true);
        DrawGrid();

    if (save_dialog_state_ != SaveDialogState::Hidden) {
        ShowSaveMapDialog();
    }
    if (clear_map_dialog_) {
        ShowClearMapConfirmationDialog();
    }
    if (test_map_error_.has_value()) {
        MapValidationErrorPopup( test_map_error_.value());
    }
}

void MapCreator::DrawToolBox() {
    const auto& config = ApplicationConfig::GetInstance();
    auto rectangle = [&](const float i) -> Rectangle {
        return Rectangle{
            20 + i * (config.button_width + config.button_spacing),
            config.button_y,
            config.button_width,
            config.button_height
        };
    };

    if (GuiButton(rectangle(0), "#162#Wall")) {
        SetCurrentTool(Tile::Wall);
    }
    if (GuiButton(rectangle(1), "#149#PlayerStart")) {
        SetCurrentTool(Tile::PlayerStart);
    }
    if (GuiButton(rectangle(2), "#146#Coin")) {
        SetCurrentTool(Tile::Coin);
    }
    if (GuiButton(rectangle(3), "#152#Enemy")) {
        SetCurrentTool(Tile::EnemyStart);
    }
    if (GuiButton(rectangle(4), "#28#Empty")) {
        SetCurrentTool(Tile::None);
    }
    if (GuiButton(rectangle(5), "#56#Clear Map")) {
        clear_map_dialog_ = true;
    }
    if (GuiButton(rectangle(6), "#101#Autofill Empty Tiles")) {
        std::ranges::replace(temporary_map_, ' ', '0');
        map_class_.LoadFromString(temporary_map_);
    }
    if (GuiButton(rectangle(7), "#2#Save Map")) {
        save_dialog_state_ = SaveDialogState::Form;
    }
    if (GuiButton(rectangle(9), "#131#Test Map")) {
        const auto res = Map::ValidateMap(temporary_map_);
        if (res.has_value()) {
            test_map_error_ = res.value();
        }else {
            test_map_error_ = std::nullopt;
            temporarily_saved_map_ = temporary_map_;
            game_->Initialize(std::nullopt, temporary_map_);
            is_active_= false;
        }
    }
    if (GuiButton(rectangle(10), "#185#Back to Main Menu")) {
        is_active_ = false;
    }
}

void MapCreator::HandlePlayerInput() {
    const auto& config = ApplicationConfig::GetInstance();
    if (save_dialog_state_ != SaveDialogState::Hidden || clear_map_dialog_) {
        return;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const int current_x = GetMouseX()- config.GameMapRootX;
        const int current_y = GetMouseY()- config.GameMapRootY;
        const int tile = Map::GetTileFromXY(current_x, current_y);
        if (tile <0 || tile >1400) {
            return;
        }
        char tile_char = ' ';

        switch (current_tool_) {
            case Tile::Coin:
                tile_char = '0';
                break;
            case Tile::Wall:
                tile_char = '#';
                break;
            case Tile::PlayerStart:
                tile_char = 'X';
                break;
            case Tile::EnemyStart:
                tile_char = '?';
                break;
            case  Tile::None:
                tile_char = ' ';
                break;
        }

        temporary_map_[tile] = tile_char;
        map_class_.LoadFromString(temporary_map_);
    }
}

void MapCreator::Initialize() {
    Activate();
    ShowCursor();

    if (temporarily_saved_map_.has_value()) {
        temporary_map_ = temporarily_saved_map_.value();
    }else {
        temporary_map_.assign(1400, ' ');
    }
    map_class_.LoadFromString(temporary_map_);
}

void MapCreator::DrawGrid() {
    const auto& config = ApplicationConfig::GetInstance();

    for ( int i =1; i<= config.TilesY; i++) {  // start at 1 since the game map draws outer borders
        DrawLine(config.GameMapRootX,config.GameMapRootY + static_cast<int>(config.TileWidth) * i, config.GameMapRootX + config.GameMapWidth, config.GameMapRootY + static_cast<int>(config.TileWidth) * i, RAYWHITE);
    }
    for ( int i =1; i<= config.TilesX; i++) {
        DrawLine(config.GameMapRootX + static_cast<int>(config.TileWidth) * i, config.GameMapRootY,config.GameMapRootX + static_cast<int>(config.TileWidth) * i, config.GameMapRootY + config.GameMapHeight, RAYWHITE);
    }
}

Rectangle MapCreator::DrawDialogBackground() {
    constexpr float dialog_width = 800;
    constexpr float dialog_height = 200;

    const Rectangle dialog = {
        .x = static_cast<float>(GetScreenWidth()) / 2 - dialog_width / 2,
        .y = static_cast<float>(GetScreenHeight()) / 2 - dialog_height / 2,
        .width = dialog_width,
        .height = dialog_height
    };
    DrawRectangle(static_cast<int>(dialog.x), static_cast<int>(dialog.y), dialog_width, dialog_height, LIGHTGRAY);
    return dialog;
}


void MapCreator::ShowSaveMapDialog() {
    const auto& config = ApplicationConfig::GetInstance();

    const Rectangle dialog = DrawDialogBackground();

    switch (save_dialog_state_) {
        case SaveDialogState::Form: {
            GuiLabel({dialog.x, dialog.y + 10, dialog.width, 30}, "Map Name:");
            if (GuiTextBox({dialog.x, dialog.y + 40, dialog.width, 30},map_name_buffer_,config.font_size,edit_name_)) {
                edit_name_ = true;
                edit_author_ = false;
            }

            GuiLabel({dialog.x, dialog.y + 80, dialog.width, 30}, "Map Author:");
            if (GuiTextBox({dialog.x, dialog.y + 110, dialog.width, 30}, map_author_buffer_,config.font_size,edit_author_)) {
                edit_author_ = true;
                edit_name_ = false;
            }

            if (GuiButton({dialog.x, dialog.y + 160, dialog.width / 2 - 5, 30}, "#2#Save")) {

                const auto res = db_->AddMap(temporary_map_, map_name_buffer_, map_author_buffer_);
                if (res.has_value()) {
                    save_dialog_state_ = SaveDialogState::Success;
                    saved_map_id_ = res.value();
                    map_created_ = true;
                }
                else {
                    save_map_error_ = res.error();
                    save_dialog_state_ = SaveDialogState::Error;

                }
            }
            if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "#113#Cancel")) {
                save_dialog_state_ = SaveDialogState::Hidden;
            }
            break;
        }

        case SaveDialogState::Success: {
            DrawText("The map was saved successfully", static_cast<int>(dialog.x), static_cast<int>(dialog.y) + 20, config.font_size_small, RED);
            if (GuiButton({dialog.x, dialog.y + 160, dialog.width/2 -5, 30}, "#131#Play")) {
                is_active_ = false;
                game_->Initialize(saved_map_id_);
            }
            if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "#113#Cancel")) {
                save_dialog_state_ = SaveDialogState::Hidden;
            }

        }
            break;

        case SaveDialogState::Error: {
            const auto res = MapValidationErrorPopup(save_map_error_.value());
            if (res) {
                save_dialog_state_ = SaveDialogState::Hidden;
            }
        }
        case SaveDialogState::Hidden:
            break;
    }
}

void MapCreator::ShowClearMapConfirmationDialog() {
    if (!clear_map_dialog_) {
        return;
    }
    const auto& config = ApplicationConfig::GetInstance();

    const Rectangle dialog = DrawDialogBackground();

    DrawText("Do you really want to clear the map?", static_cast<int>(dialog.x), static_cast<int>(dialog.y) + 20, config.font_size_small, RED);
    if (GuiButton({dialog.x, dialog.y + 160, dialog.width/2 -5, 30}, "#112#Yes")) {
        temporary_map_.assign(1400, ' ');
        map_class_.LoadFromString(temporary_map_);
        clear_map_dialog_ = false;


    }
    if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "#113#Cancel")) {
        clear_map_dialog_ = false;
    }

}

bool MapCreator::MapValidationErrorPopup(const MapValidationError error) {
    const Rectangle dialog = DrawDialogBackground();
    const auto& config = ApplicationConfig::GetInstance();
    std::string error_message;
    switch (error) {
        case MapValidationError::InvalidLength:
            error_message = "Invalid Map Length";
            break;
        case MapValidationError::InvalidPlayerCount:
            error_message = "There needs to be exactly one player";
            break;
        case MapValidationError::InvalidEnemyCount:
            error_message = "There need to be between 1 and 4 enemies";
            break;
        case MapValidationError::UnresolvableSymbols:
            error_message = "This shouldn't have happened";
            break;
        case MapValidationError::CoinsUnreachable:
            error_message = "Some coins are unreachable"; // needs to be added later
            break;
        case MapValidationError::TooFewCoins:
            error_message = "Too few coins. Minimum is 100";
            break;
        case MapValidationError::DatabaseError:
            error_message = "Some database error";
            break;
    }
    DrawText(std::format("Error: {}", error_message).c_str(), static_cast<int>(dialog.x), static_cast<int>(dialog.y) + 20, config.font_size_small, RED);
    if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "#113#Cancel")) {
        test_map_error_ = std::nullopt;
        return true;
    }
    return false;
}


bool MapCreator::MapCreated() {
    return std::exchange(map_created_, false);
}


