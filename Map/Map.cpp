//
// Created by simon on 22.02.26.
//


#include "Map/Map.h"

#include <iostream>
#include "Database/Database.h"
#include <algorithm>
#include <utility>
#include <raylib.h>
#include <regex>
#include "ApplicationConfig.h"

Map::Map(Database* db) : db_(db) {
}

Map::Map() {
    db_ = nullptr;
}

int Map::GetTileFromXY(const int x, const int y) {
    const auto& config = ApplicationConfig::GetInstance();
    const int tile_x = x / static_cast<int>(config.TileWidth);
    const int tile_y = y / static_cast<int>(config.TileWidth);
    return tile_x + tile_y * config.TilesX;
}

void Map::Draw(const bool editor) const {
    const auto& config = ApplicationConfig::GetInstance();
    for (int i = 0; i < loaded_map_.size(); i++) {
        const int tile_x = (i % config.TilesX) * static_cast<int>(config.TileWidth) + config.GameMapRootX;
        const int tile_y = (i / config.TilesX) * static_cast<int>(config.TileWidth) + config.GameMapRootY;

        const int center_x = tile_x + static_cast<int>(config.TileWidth) / 2;
        const int center_y = tile_y + static_cast<int>(config.TileWidth) / 2;

        if (loaded_map_.at(i) == '#') {
            DrawRectangle(tile_x, tile_y, static_cast<int>(config.TileWidth), static_cast<int>(config.TileWidth), RAYWHITE);
        }
        if (!editor) {
            if (loaded_map_.at(i) == '0' && !explored_map_.at(i)) {
                DrawCircle(center_x, center_y, config.PointRadius * 0.5f, GREEN); // the coins should be smaller than player
            }
        }
        else {
            if (loaded_map_.at(i) == 'X' ) {
                DrawText("X", center_x - static_cast<int> (config.TileWidth/2) , center_y- static_cast<int>(config.TileWidth/2),static_cast<int>(config.TileWidth), LIME);
            }
            if (loaded_map_.at(i)== '?') {
                DrawText("?", center_x - static_cast<int> (config.TileWidth/2) , center_y- static_cast<int> (config.TileWidth/2),static_cast<int>(config.TileWidth), LIME);
            }
            if (loaded_map_.at(i) == '0') {
                DrawCircle(center_x, center_y, config.PointRadius * 0.5f, GREEN);
            }
        }
    }
    //these are the outer borders that get drawn when there is a small gap
    DrawRectangle(0, config.GameMapRootY, config.GameMapRootX, config.GameMapHeight, RAYWHITE);
    DrawRectangle(GetScreenWidth() -config.GameMapRootX, config.GameMapRootY, config.GameMapRootX, config.GameMapHeight, RAYWHITE);
    DrawRectangle(0, config.GameMapRootY - config.GameMapRootX, GetScreenWidth(), config.GameMapRootX, RAYWHITE);
    DrawRectangle(0, config.GameMapRootY + config.GameMapHeight, GetScreenWidth(), config.GameMapRootX, RAYWHITE);
}



std::string Map::GetMap() {
    return loaded_map_;
}

bool Map::AllExplored() const {
    return free_tile_count_ == score_;
}

void Map::Explore(const int tile) {
    if (tile<0 || tile>= loaded_map_.size()) return;

    if (!explored_map_.at(tile) && loaded_map_.at(tile) == '0') {
        explored_map_.at(tile) = true;
        score_++;
    }
}



bool Map::CanMove(const int tile) const {
    const auto& config = ApplicationConfig::GetInstance();
    if (tile < 0 || tile >= config.TilesX * config.TilesY)
        return false;

    return loaded_map_.at(tile) != '#';

}


std::pair<float, float> Map::GetTileCenter(const int tile) {
    const auto& config = ApplicationConfig::GetInstance();

    if ( tile > config.TilesX * config.TilesY) {
        return {-1.f,-1.f};
    }

    const float center_x = static_cast<float>(config.GameMapRootX) + static_cast<float>(tile % config.TilesX) * config.TileWidth + config.TileWidth / 2;
    const float center_y = static_cast<float>(config.GameMapRootY) + static_cast<float>(tile / config.TilesX) * config.TileWidth + config.TileWidth / 2;

    return {center_x, center_y};
}

int Map::FindPlayerStartTile() const {
    const auto pos = loaded_map_.find('X');
    if (pos == std::string::npos) {
        return 0; // default value should never be called
    }
    return static_cast<int>(pos);
}

std::vector<int> Map::FindEnemyStartTiles() const {
    std::vector<int> positions;
    for (int i = 0; i < loaded_map_.size(); ++i) {
        if (loaded_map_[i] == '?') positions.push_back(i);
    }
    return positions;
}

void Map::LoadFromString(const std::string& map) {
    loaded_map_ = map;
    score_ = 0;
    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(
        std::ranges::count(loaded_map_, '0')
    );
}


void Map::LoadMapFromDB(const int map_number) {
    score_ = 0;
    auto result = db_->GetMap(map_number);
    loaded_map_ = std::move(result.value()); //move avoids copy
    std::erase(loaded_map_, '\n');
    std::erase(loaded_map_, '\r');
    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(
        std::ranges::count(loaded_map_, '0')
    );
}

std::optional<MapValidationError> Map::ValidateMap(const std::string& map) {
    static const std::regex valid_chars(R"(^[X#0? ]+$)");

    if (map.length() != 1400) {
        return MapValidationError::InvalidLength;
    }
    if (std::ranges::count(map, '0')<=100) {
        std::cerr << "Not enough coins" << std::endl;
        return MapValidationError::TooFewCoins;
    }
    if (!std::regex_match(map, valid_chars)) {
        std::cerr << "Invalid characters found.\n";
        return MapValidationError::UnresolvableSymbols;
    }
    auto player_starting_positions_count = std::ranges::count(map, 'X');
    if (player_starting_positions_count != 1) {
        std::cerr << "Invalid player count: " << player_starting_positions_count << " (expected exactly 1)\n";
        return MapValidationError::InvalidPlayerCount;
    }
    auto ghost_starting_positions_count = std::ranges::count(map, '?');
    if (ghost_starting_positions_count > 4 || ghost_starting_positions_count < 1) {
        std::cerr << "Invalid ghost count: (Must be between 1 and 4) current count: " << ghost_starting_positions_count << "\n";
        return MapValidationError::InvalidEnemyCount;
    }
    return std::nullopt;
}
