//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

#include <algorithm>
#include <raygui.h>
#include <raylib.h>

#include "../ApplicationConfig.h"


MapCreator::MapCreator(Database *database): db_(database)
{
    is_active_ = false;

}


void MapCreator::DrawFrame() {
    const auto& config = ApplicationConfig::GetInstance();



        ClearBackground(BLACK);
        DrawToolBox();
        map_class_.Draw(true);
        DrawGrid();
    if (show_save_dialog_) {
        SaveMapDialog();
    }
}



void MapCreator::DrawToolBox() {
    const auto& config = ApplicationConfig::GetInstance();

    constexpr int button_width = 150;
    constexpr int button_height = 50;
    constexpr int button_y = 20; // top bar
    constexpr int spacing = 10;

    constexpr Rectangle wall_button = {
        static_cast<float>(20 + 0 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    const Rectangle coin_button = {
        static_cast<float>(20 + 1 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    const Rectangle player_start_button = {
        static_cast<float>(20 + 2 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    const Rectangle enemy_start_button = {
        static_cast<float>(20 + 3 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    const Rectangle empty_button = {
        static_cast<float>(20 + 4 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    const Rectangle clear_button = {
        static_cast<float>(20 + 5 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
   const Rectangle autofill_button = {
       static_cast<float>(20 + 6 * (button_width + spacing)),
       static_cast<float>(button_y),
       static_cast<float>(button_width),
       static_cast<float>(button_height)
   };
   const Rectangle save_map_button = {
       static_cast<float>(20 + 7 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
   };
    const Rectangle back_to_main_menu = {
        static_cast<float>(20 + 8 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)

    };


    if (GuiButton(wall_button, "Wall")) {
        SetCurrentTool(Tile::Wall);
    }
    if (GuiButton(player_start_button, "PlayerStart")) {
        SetCurrentTool(Tile::PlayerStart);
    }
    if (GuiButton(coin_button, "Coin")) {
        SetCurrentTool(Tile::Coin);
    }
    if (GuiButton(enemy_start_button, "Enemy")) {
        SetCurrentTool(Tile::EnemyStart);
    }
    if (GuiButton(empty_button, "Empty")) {
        SetCurrentTool(Tile::None);
    }
    if (GuiButton(clear_button, "Empty Map")) {
        temporary_map_.assign(1400, ' ');
        map_class_.LoadFromString(temporary_map_);
    }
    if (GuiButton(autofill_button, "Autofill Empty Tiles with coins")) {
        std::ranges::replace(temporary_map_, ' ', '0');
        map_class_.LoadFromString(temporary_map_);
    }
    if (GuiButton(save_map_button, "Save Map")) {
        show_save_dialog_ = true;
    }
    if (GuiButton(back_to_main_menu, "Back to Main Menu")) {
        is_active_ = false;
    }
}

void MapCreator::HandlePlayerInput() {
    if (show_save_dialog_) {
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
    is_active_ = true;
    temporary_map_.assign(1400, ' ');
    map_class_.LoadFromString(temporary_map_);

}

void MapCreator::DrawGrid() {
    const auto& config = ApplicationConfig::GetInstance();

    for ( int i =1; i<= config.TilesY; i++) { // start at 1 since the game map draws outer borders
        DrawLine(config.GameMapRootX,config.GameMapRootY + config.TileWidth*i, config.GameMapRootX+ config.GameMapWidth, config.GameMapRootY+config.TileWidth*i, RAYWHITE);
    }
    for ( int i =1; i<= config.TilesX; i++) {
        DrawLine(config.GameMapRootX+ config.TileWidth*i, config.GameMapRootY,config.GameMapRootX+config.TileWidth*i, config.GameMapRootY+config.GameMapHeight, RAYWHITE);
    }
}


void MapCreator::SaveMapDialog() {
    const auto& config = ApplicationConfig::GetInstance();
    constexpr int dialog_width = 800;
    constexpr int dialog_height = 200;

    const Rectangle dialog = {
        .x = static_cast<float>(GetScreenWidth() / 2 - dialog_width / 2),
        .y = static_cast<float>(GetScreenHeight() / 2 - dialog_height / 2),
        .width = static_cast<float>(dialog_width),
        .height = static_cast<float>(dialog_height)
    };
    DrawRectangle(dialog.x, dialog.y, dialog_width, dialog_height, LIGHTGRAY);

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

    if (GuiButton({dialog.x, dialog.y + 160, dialog.width / 2 - 5, 30}, "Save")) {
        show_save_dialog_ = false;
        auto res = db_->AddMap(temporary_map_, map_name_buffer_, map_author_buffer_);
        if (!res) {


        }
    }
    if (GuiButton({dialog.x + dialog.width / 2 + 5, dialog.y + 160, dialog.width / 2 - 5, 30}, "Cancel")) {
        show_save_dialog_ = false;
    }
}

