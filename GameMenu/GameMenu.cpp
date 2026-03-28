//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "../Game/Game.h"
#include "../config.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


GameMenu::~GameMenu() = default;

GameMenu::GameMenu(Game *game): game_(game) {
}

void GameMenu::Show() const {
    DrawText("PAC-MAN GAME",
             WindowConfig::WindowWidth / 2 - 150,
             100,
             40,
             BLACK);


    constexpr Rectangle default_map_button_ = {
        static_cast<float>(WindowConfig::WindowWidth / 2 - 100),
        static_cast<float>(WindowConfig::WindowHeight / 2 - 50),
        200,
        50
    };
    constexpr Rectangle map_2_button_ = {
        static_cast<float>(WindowConfig::WindowWidth / 2 - 100),
        static_cast<float>(WindowConfig::WindowHeight / 2 - 0),
        200,
        50
    };

    if (GuiButton(default_map_button_, "Use Default Map")) {
        game_->Initialize(1);
    }
    if (GuiButton(map_2_button_, "Use Map2")) {
        game_->Initialize(2);
    }

}

