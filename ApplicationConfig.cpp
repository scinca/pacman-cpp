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


}


ApplicationConfig::~ApplicationConfig() {
    CloseWindow();
}
