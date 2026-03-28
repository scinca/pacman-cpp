//
// Created by simon on 28.03.26.
//
#include <raylib.h>

#include "ApplicationConfig.h"


ApplicationConfig::ApplicationConfig() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), window_title_.c_str());
    SetTargetFPS(60);
    screen_width_ = GetScreenWidth();
    screen_height_ = GetScreenHeight();
    TileWidth = std::min(screen_width_ / TilesX,screen_height_ / TilesY);
    PointRadius = TileWidth * 0.8 / 2;
    GameMapWidth = TileWidth * TilesX;
    GameMapHeight = TileWidth * TilesY;
    GameMapRootY = (screen_height_ - GameMapHeight) - (GetScreenWidth()- GameMapWidth)/2;
    GameMapRootX = (screen_width_ - GameMapWidth) / 2;

}


ApplicationConfig::~ApplicationConfig() {
    CloseWindow();
}
