//
// Created by simon on 29.03.26.
//

#include "MapCreator.h"

#include <raylib.h>

#include "../ApplicationConfig.h"


MapCreator::MapCreator(Database *database): db_(database)
{
    is_active_ = false;

}


void MapCreator::DrawFrame() {
    const auto& config = ApplicationConfig::GetInstance();

    ClearBackground(BLACK);
    map_class_.Draw();

}

void MapCreator::Initialize() {
    is_active_ = true;
    temporary_map_.assign(1400, ' ');
    map_class_.LoadFromString(temporary_map_);

}

void MapCreator::DrawGrid() {
    const auto& config = ApplicationConfig::GetInstance();


}

