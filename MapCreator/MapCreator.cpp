//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

#include <raylib.h>

#include "../ApplicationConfig.h"


MapCreator::MapCreator(Database *database): db_(database)
{
    is_active_ = false;

}


void MapCreator::DrawFrame() {
    const auto& config = ApplicationConfig::GetInstance();

    ClearBackground(BLACK);
    map_class_.Draw();
    DrawGrid();
}

void MapCreator::Update() {
    const auto& config = ApplicationConfig::GetInstance();

    map_class_.LoadFromString(temporary_map_);
}



void MapCreator::DrawToolBox() {
    const auto& config = ApplicationConfig::GetInstance();

    const int button_width = 150;
    const int button_height = 50;
    const int button_y = 20; // top bar
    const int spacing = 10;

    Rectangle wall_button = {
        static_cast<float>(20 + 0 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    Rectangle coin_button = {
        static_cast<float>(20 + 1 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    Rectangle player_start_button = {
        static_cast<float>(20 + 2 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    Rectangle enemy_start_button = {
        static_cast<float>(20 + 3 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };
    Rectangle empty_button = {
        static_cast<float>(20 + 4 * (button_width + spacing)),
        static_cast<float>(button_y),
        static_cast<float>(button_width),
        static_cast<float>(button_height)
    };



}

void MapCreator::HandlePlayerInput() {
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



