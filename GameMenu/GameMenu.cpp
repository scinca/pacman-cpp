//
// Created by simon on 14.03.26.
//

#include "GameMenu.h"
#include "Game/Game.h"
#include "ApplicationConfig.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "Database/Database.h"
#include <iostream>

GameMenu::~GameMenu() = default;

GameMenu::GameMenu(Game *game, MapCreator *map_creator, Database *db): game_(game), map_creator_(map_creator), db_(db) {
    maps_ = db_->GetAllMaps();
}

void GameMenu::ReloadMaps() { //leaving this in for readability since gcc will inline it.
    maps_ = db_->GetAllMaps();
}

void GameMenu::Show() {
    if (map_creator_->MapCreated()) {
        ReloadMaps();
    }
    constexpr float button_width = 200;
    constexpr float button_height = 50;
    const auto& config = ApplicationConfig::GetInstance();
    DrawText("PAC-MAN GAME",
             config.GameMapWidth / 2 - 150,
             100,
             config.font_size,
             BLACK);


    const Rectangle create_map_button = {
        static_cast<float>(GetScreenWidth())/2 - button_width/2,
        static_cast<float>(config.GameMapHeight) /4 ,
        button_width,
        button_height,
    };

    if (GuiButton(create_map_button, "Create  your own Map")) {
        map_creator_->Initialize();
    }

   for (int i = 0; i != maps_.size(); i++ ) {
       DrawMapInfo(maps_.at(i), i+1);
   }

}


void GameMenu::DrawMapInfo(const MapInfo& data, const int i) const {
    const auto& config = ApplicationConfig::GetInstance();

    constexpr float row_height = 40;
    const float start_y = static_cast<float>(GetScreenHeight()) / 3.0f;
    const float start_x = static_cast<float>(GetScreenWidth()) / 10.0f * 2;

    constexpr float id     = 60;
    constexpr float name   = 250;
    constexpr float author = 250;
    constexpr float date   = 200;
    constexpr float button    = 100;
    constexpr float total_width = id + name + author + date+ button;

    const float y = start_y + row_height * i;

    const Color background = (i % 2 == 0) ? LIGHTGRAY : GRAY;

    DrawRectangle(start_x, y, total_width, row_height, background);

    const int text_y = y + (row_height - config.font_size) / 2;
    DrawText(std::to_string(i).c_str(),    start_x,                              text_y, config.font_size/2, BLACK);
    DrawText(data.name.c_str(),                  start_x + id,                     text_y, config.font_size/2, BLACK);
    DrawText(data.author.c_str(),                start_x + id + name,          text_y, config.font_size/2, BLACK);
    DrawText(data.creation_date.c_str(),         start_x + id + name + author, text_y, config.font_size/2, BLACK);

    if (GuiButton({start_x + total_width, y, button, row_height}, "Play")) {
        game_->Initialize(data.id);

        std::cout<<data.content << std::endl;
    }
}

