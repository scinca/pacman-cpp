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


}
void MapCreator::HandlePlayerInput() {
    const auto& config = ApplicationConfig::GetInstance();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int current_x = GetMouseX()- config.GameMapRootX;
        int current_y = GetMouseY()- config.GameMapRootY;
        int tile = Map::GetTileFromXY(current_x, current_y);
        if



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



