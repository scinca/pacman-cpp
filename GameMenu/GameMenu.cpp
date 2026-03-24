//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "../Game/Game.h"
#include "../config.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


GameMenu::~GameMenu() {
}

GameMenu::GameMenu(Game *game): game_(game) {
}

void GameMenu::ShowMenu() const {
    DrawText("PAC-MAN GAME",
             WindowConfig::WindowWidth / 2 - 150,
             100,
             40,
             BLACK);

    // Default Map Button
    constexpr Rectangle defaultMapButton = {
        static_cast<float>(WindowConfig::WindowWidth / 2 - 100),
        static_cast<float>(WindowConfig::WindowHeight / 2 - 25),
        200,
        50
    };

    if (GuiButton(defaultMapButton, "Use Default Map")) {
        game_->Initialize();

    }

}

