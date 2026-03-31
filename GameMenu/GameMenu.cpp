//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "../Game/Game.h"
#include "../ApplicationConfig.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


GameMenu::~GameMenu() = default;

GameMenu::GameMenu(Game *game, MapCreator *map_creator): game_(game), map_creator_(map_creator) {
}

void GameMenu::Show() const {
    constexpr int button_width = 200;
    constexpr int button_height = 50;
    const auto& config = ApplicationConfig::GetInstance();
    DrawText("PAC-MAN GAME",
             config.GameMapWidth / 2 - 150,
             100,
             config.font_size,
             BLACK);


    const Rectangle create_map_button = {
        static_cast<float>(GetScreenWidth()/2 - button_width/2),
        static_cast<float>(config.GameMapHeight /4 ),
        button_width,
        button_height,
    };

    if (GuiButton(create_map_button, "Create  your own Map")) {
        map_creator_->Initialize();

    }


}

