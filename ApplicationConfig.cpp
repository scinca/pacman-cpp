//
// Created by simon on 28.03.26.
//
#include <raylib.h>

#include "ApplicationConfig.h"

#include "MapCreator/MapCreator.h"


ApplicationConfig::ApplicationConfig() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), window_title_.c_str());
    SetTargetFPS(60);
    screen_width_ = GetScreenWidth();
    screen_height_ = GetScreenHeight();
    TileWidth = static_cast<float>(std::min(screen_width_ / TilesX,screen_height_ / TilesY));
    PointRadius = TileWidth * 0.8f / 2;
    GameMapWidth = static_cast<int>(TileWidth) * TilesX;
    GameMapHeight = static_cast<int>(TileWidth) * TilesY;
    GameMapRootY = (screen_height_ - GameMapHeight) - (GetScreenWidth()- GameMapWidth)/2;
    GameMapRootX = (screen_width_ - GameMapWidth) / 2;
    velocity_ = TileWidth * 4.0f;
    margin_ = TileWidth / 10.0f;

}


ApplicationConfig::~ApplicationConfig() {
    CloseWindow();
}
