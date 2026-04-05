//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

#include <algorithm>
#include <format>
#include <raygui.h>
#include <raylib.h>

#include "../ApplicationConfig.h"


MapCreator::MapCreator(Database *database, Game *game): game_(game), db_(database)
{
    is_active_ = false;

}


void MapCreator::DrawFrame() {
    const auto& config = ApplicationConfig::GetInstance();
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


    const Rectangle wall_button = {
        static_cast<float>(20 + 0 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle coin_button = {
        static_cast<float>(20 + 1 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle player_start_button = {
        static_cast<float>(20 + 2 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle enemy_start_button = {
        static_cast<float>(20 + 3 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle empty_button = {
        static_cast<float>(20 + 4 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle clear_button = {
        static_cast<float>(20 + 5 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
    };
    const Rectangle autofill_button = {
       static_cast<float>(20 + 6 * (config.button_width + config.button_spacing)),
       static_cast<float>(config.button_y),
       static_cast<float>(config.button_width),
       static_cast<float>(config.button_height)
   };
    const Rectangle save_map_button = {
       static_cast<float>(20 + 7 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)
   };
    const Rectangle test_game_button = {
        static_cast<float>(20 + 9 * (config.button_width + config.button_spacing)),
      static_cast<float>(config.button_y),
      static_cast<float>(config.button_width),
      static_cast<float>(config.button_height)

    };
    const Rectangle back_to_main_menu = {
        static_cast<float>(20 + 10 * (config.button_width + config.button_spacing)),
        static_cast<float>(config.button_y),
        static_cast<float>(config.button_width),
        static_cast<float>(config.button_height)

    };


    if (GuiButton(wall_button, "#162#Wall")) {
        SetCurrentTool(Tile::Wall);
    }
    if (GuiButton(player_start_button, "#149#PlayerStart")) {
        SetCurrentTool(Tile::PlayerStart);
    }
    if (GuiButton(coin_button, "#146#Coin")) {
        SetCurrentTool(Tile::Coin);
    }
    if (GuiButton(enemy_start_button, "#152#Enemy")) {
        SetCurrentTool(Tile::EnemyStart);
    }
    if (GuiButton(empty_button, "#28#Empty")) {
        SetCurrentTool(Tile::None);
    }
    if (GuiButton(clear_button, "#56#Clear Map")) {
        clear_map_dialog_ = true;
    }
    if (GuiButton(autofill_button, "#101#Autofill Empty Tiles")) {
        std::ranges::replace(temporary_map_, ' ', '0');
        map_class_.LoadFromString(temporary_map_);
    }
    if (GuiButton(save_map_button, "#2#Save Map")) {
        save_dialog_state_ = SaveDialogState::Form;
    }
    if (GuiButton(test_game_button, "#131#Test Map")) {
        auto res = Map::ValidateMap(temporary_map_);
        if (res.has_value()) {
            test_map_error_ = res.value();
        }else {
            test_map_error_ = std::nullopt;
            temporarily_saved_map_ = temporary_map_;
            game_->Initialize(std::nullopt, temporary_map_);
            is_active_= false;
        }
    }
    if (GuiButton(back_to_main_menu, "#185#Back to Main Menu")) {
        is_active_ = false;

    }
}
void MapCreator::Activate() {
    is_active_ = true;
}

void MapCreator::HandlePlayerInput() {
    if (save_dialog_state_ != SaveDialogState::Hidden || clear_map_dialog_) {
        return;
    }

    const auto& config = ApplicationConfig::GetInstance();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        const int current_x = GetMouseX()- config.GameMapRootX;
        const int current_y = GetMouseY()- config.GameMapRootY;
        const int tile = Map::GetTileFromXY(current_x, current_y);
        if (tile <0 || tile >1400) {
            return;
        }

        char tile_char = '0';

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
    ShowCursor();
    Activate();
    if (temporarily_saved_map_.has_value()) {
        temporary_map_ = temporarily_saved_map_.value();
    }else {
        temporary_map_.assign(1400, ' ');
    }

    map_class_.LoadFromString(temporary_map_);

}

void MapCreator::DrawGrid() {
    const auto& config = ApplicationConfig::GetInstance();

    for ( int i =1; i<= config.TilesY; i++) { // start at 1 since the game map draws outer borders
        DrawLine(config.GameMapRootX,config.GameMapRootY + config.TileWidth* i, config.GameMapRootX+ config.GameMapWidth, config.GameMapRootY+config.TileWidth*i, RAYWHITE);
    }
    for ( int i =1; i<= config.TilesX; i++) {
        DrawLine(config.GameMapRootX + config.TileWidth* i, config.GameMapRootY,config.GameMapRootX+config.TileWidth*i, config.GameMapRootY+config.GameMapHeight, RAYWHITE);
    }
}

Rectangle MapCreator::DrawDialogBackground() {
    constexpr float dialog_width = 800;
    constexpr float dialog_height = 200;

    const Rectangle dialog = {
        .x = static_cast<float>(GetScreenWidth()) / 2 - dialog_width / 2,
        .y = static_cast<float>(GetScreenHeight()) / 2 - dialog_height / 2,
        .width = static_cast<float>(dialog_width),
        .height = static_cast<float>(dialog_height)
    };
    DrawRectangle(dialog.x, dialog.y, dialog_width, dialog_height, LIGHTGRAY);
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
            DrawText("The map was saved successfully", dialog.x, dialog.y+ 20, config.font_size - 10, RED);
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
            const auto res = MapValidationErrorPopup(save_map_error_);
            if (res) {
                save_dialog_state_ = SaveDialogState::Hidden;
            }
        }
        default: ;
    }
}

void MapCreator::ShowClearMapConfirmationDialog() {
    if (!clear_map_dialog_) {
        return;
    }
    const auto& config = ApplicationConfig::GetInstance();

    const Rectangle dialog = DrawDialogBackground();

    DrawText("Do you really want to clear the map?", dialog.x, dialog.y+ 20, config.font_size - 10, RED);
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
    DrawText(std::format("Error: {}", error_message).c_str(), dialog.x, dialog.y+ 20, config.font_size - 10, RED);
    if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "#113#Cancel")) {
        test_map_error_ = std::nullopt;
        return true;
    }

    return false;
}

// I want to return whether a map was created and then reset this variable so the GameMenu is updated only once.
bool MapCreator::MapCreated() {

    return std::exchange(map_created_, false); // better than making a temporary variable and then

}


