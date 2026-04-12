//
// Created by simon on 28.03.26.
//
#include <raylib.h>
#include <algorithm>
#include "ApplicationConfig.h"
#include "MapCreator/MapCreator.h"


ApplicationConfig::ApplicationConfig() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), window_title_.c_str());
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    ToggleFullscreen();
    screen_width_ = GetScreenWidth();
    screen_height_ = GetScreenHeight();
    TileWidth = static_cast<float>(std::min(screen_width_ / TilesX,screen_height_ / TilesY));
    PointRadius = TileWidth * 0.8f / 2;
    GameMapWidth = static_cast<int>(TileWidth) * TilesX;
    GameMapHeight = static_cast<int>(TileWidth) * TilesY;
    GameMapRootY = (screen_height_ - GameMapHeight) - (screen_width_- GameMapWidth)/2;
    GameMapRootX = (screen_width_ - GameMapWidth) / 2;
    Velocity = TileWidth * 4.0f;
    Margin = TileWidth / 7.5f;
    ButtonSpacing = static_cast<float>(screen_width_) / 100;
    ButtonWidth = static_cast<float>(screen_width_) / 13;
    ButtonHeight = static_cast<float>(screen_height_) /20;
    FontSize = screen_width_ /48;
    FontSizeSmall = static_cast<int>(static_cast<float>(FontSize) * 0.75f);

}


ApplicationConfig::~ApplicationConfig() {
    CloseWindow();
}
