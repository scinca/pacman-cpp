//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "../Game/Game.h"
#include "../ApplicationConfig.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


GameMenu::~GameMenu() = default;

GameMenu::GameMenu(Game *game): game_(game) {
}

void GameMenu::Show() const {
    const auto& config = ApplicationConfig::GetInstance();
    DrawText("PAC-MAN GAME",
             config.GameMapWidth / 2 - 150,
             100,
             config.font_size,
             BLACK);


    const Rectangle default_map_button_ = {
        static_cast<float>(config.GameMapWidth / 2 - 100),
        static_cast<float>(config.GameMapHeight / 2 - 50),
        200,
        50
    };



    if (GuiButton(default_map_button_, "Use Default Map")) {
        game_->Initialize(1);
    }
}

