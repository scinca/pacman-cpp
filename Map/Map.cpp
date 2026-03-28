//
// Created by simon on 22.02.26.
//

#include "Map.h"
#include "../Database/Database.h"
#include <fstream>
#include <iostream>

#include "../config.h"
#include <raylib.h>
#include <regex>

Map::Map(Database* db){
 database_ = db;
}




void Map::Draw() const {
    for (int i = 0; i < loaded_map_.size(); i++) {
        const std::int32_t tile_x = (i % 50) * TileWidth + WindowConfig::WindowRoot;
        const std::int32_t tile_y = (i / 50) * TileWidth + WindowConfig::WindowRoot;

        const int center_x = tile_x + TileWidth / 2;
        const int center_y = tile_y + TileWidth / 2;

        if (loaded_map_[i] == '#') {
            DrawRectangle(tile_x, tile_y, TileWidth, TileWidth, RAYWHITE);
        }
        if (loaded_map_[i] == '0' && !explored_map_[i]) {
            DrawCircle(center_x, center_y, PointRadius * 0.5, GREEN);
        }
    }
}

std::string Map::GetMap() {
    return loaded_map_;
}

bool Map::AllExplored() const {
    return free_tile_count_ == explored_tile_count_;
}

void Map::Explore(const int tile) {
    if (tile<0 || tile> loaded_map_.size()) return;

    if (!explored_map_[tile]&& loaded_map_[tile] == '0') {
        explored_map_[tile] = true;
        explored_tile_count_++;
    }
}


bool Map::IsExplored(const int x, const int y) const { //tbr
    if (x < 0 || x >= 50 || y < 0 || y >= 28) return false;
    return explored_map_[y * 50 + x];
}

bool Map::CanMove(const int tileNumber) const {
    if (tileNumber < 0 || tileNumber >= static_cast<int>(loaded_map_.size()))
        return false;

    return loaded_map_[tileNumber] != '#';

}


std::pair<float, float> Map::GetTileCenter(const int tile) {
    const float center_x = WindowConfig::WindowRoot + (tile % 50) * TileWidth + TileWidth / 2;
    const float center_y = WindowConfig::WindowRoot + (tile / 50) * TileWidth + TileWidth / 2;
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



std::expected<void, std::string> Map::LoadMapFromDB(const int map_number) {
    auto result = database_->GetMap(map_number);
    if (!result) {
        return std::unexpected("Map " + std::to_string(map_number) + " not found");
    }

    loaded_map_ = std::move(result.value()); //move avoids copy
    std::erase(loaded_map_, '\n');
    std::erase(loaded_map_, '\r');

    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(
        std::count(loaded_map_.begin(), loaded_map_.end(), '0')
    );

    return {};
}

/*
std::expected<void, std::string> Map::Load(const std::string& filename) { // should expect a 50x 28 grid
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return std::unexpected("Failed to open file: " + filename);
    }

    loaded_map_.assign((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    std::erase(loaded_map_, '\n'); //remove newline so for loop can draw map.
    std::erase(loaded_map_, '\r'); // needed on Windows
    if (loaded_map_.length() != 1400) { // the grid is 50 x 28 so its total length is 1400
        return std::unexpected("Error loading Map, Map doesn't fit into the grid. Current Length:" + std::to_string(loaded_map_.length()));
    }

    if (file.fail() && !file.eof()) {
        return std::unexpected("Error reading file: " + filename);
    }
    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(std::count(loaded_map_.begin(), loaded_map_.end(), '0'));

    return {};

}
*/

void Map::LoadDefaultMap() {
    const auto result = database_->GetMap(1);
    if (!result) {
        std::cerr << "Map " + std::to_string(1) + " not found\n";
        return;
    }
    loaded_map_ = result.value();


    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(std::count(loaded_map_.begin(), loaded_map_.end(), '0'));

}

void Map::LoadMap2() {
    loaded_map_ = map_2_;
    std::erase(loaded_map_, '\n');
    std::erase(loaded_map_, '\r');
    if (loaded_map_.length() != 1400) {
        std::cout << ("Invalid map length: " + std::to_string(loaded_map_.length()));
    }
    explored_map_.assign(loaded_map_.size(), false);
    free_tile_count_ = static_cast<int>(std::count(loaded_map_.begin(),loaded_map_.end(), '0'));
}

bool Map::ValidateMap(const std::string& map) {
    /*
     *ValidateMap() Checks if the map has correct length,
     *only allowed symbols
     *and the correct number of starting positions
     */
    static const std::regex valid_chars(R"(^[X#0? ]+$)");

    if (map.length() != 1400) {
        return false;
    }

    if (!std::regex_match(map, valid_chars)) {
        std::cerr << "Invalid characters found.\n";
        return false;
    }

    int player_starting_positions_count = std::count(map.begin(), map.end(), 'X');
    if (player_starting_positions_count != 1) {
        std::cerr << "Invalid player count: " << player_starting_positions_count << " (expected exactly 1)\n";
        return false;
    }

    int ghost_starting_positions_count = std::count(map.begin(), map.end(), '?');
    if (ghost_starting_positions_count > 4 || ghost_starting_positions_count < 1) {
        std::cerr << "Invalid ghost count: (Must be between 1 and 4) current count: " << ghost_starting_positions_count << "\n";
        return false;
    }

    return true;
}
