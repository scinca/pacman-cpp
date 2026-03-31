//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "../Game/Game.h"
#include "../ApplicationConfig.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "../Database/Database.h"


GameMenu::~GameMenu() = default;

GameMenu::GameMenu(Game *game, MapCreator *map_creator, Database *db): game_(game), map_creator_(map_creator), db_(db) {
    maps = db_->GetAllMaps();
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

    DrawMapInfo(maps[0], 1);

}


void GameMenu::DrawMapInfo(const MapInfo& data, int i) const {
    float width = GetScreenWidth() / 8;
    float start =  GetScreenHeight() / 3;
    float height = 20;

    GuiLabel({width, start + height * i, width, height }, std::to_string(data.id).c_str());
    GuiLabel({width * 2, start + height * i, width, height }, data.name.c_str());
    GuiLabel({width * 3, start + height * i, width, height }, data.author.c_str());
    GuiLabel({width * 4, start + height * i, width, height }, data.creation_date.c_str());
    if (GuiButton({width*5, start + height * i, width, height }, "Play")) {
        game_->Initialize(data.id);
    }

}

