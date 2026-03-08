//
// Created by simon on 22.02.26.
//

#include "map.h"

#include <fstream>

#include "../config.h"
#include <raylib.h>

std::expected<void, std::string> Map::load(const std::string& filename) { // should expect a 50x 28 grid
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return std::unexpected("Failed to open file: " + filename);
        }

        loaded_map.assign((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        std::erase(loaded_map, '\n'); //remove newline so for loop can draw map.
        std::erase(loaded_map, '\r'); // needed on Windows
        if (loaded_map.length() != 1400) { // the grid is 50 x 28 so its total length is 1400
            return std::unexpected("Error loading Map, Map doesn't fit into the grid. Current Length:" + std::to_string(loaded_map.length()));
        }

        if (file.fail() && !file.eof()) {
            return std::unexpected("Error reading file: " + filename);
        }
        explored_map.assign(loaded_map.size(), false);
        freeTileCount = static_cast<int>(count(loaded_map.begin(), loaded_map.end(), '0'));

        return {};

    }





void Map::draw() const {
    for (int i = 0; i < loaded_map.size(); i++) {
        const std::int32_t tile_x = (i % 50) * TileWidth + WindowConfig::WindowRoot;
        const std::int32_t tile_y = (i / 50) * TileWidth + WindowConfig::WindowRoot;

        const int center_x = tile_x + TileWidth / 2;
        const int center_y = tile_y + TileWidth / 2;

        if (loaded_map[i] == '#') {
            DrawRectangle(tile_x, tile_y, TileWidth, TileWidth, RAYWHITE);
        }
        if (loaded_map[i] == '0' && !explored_map[i]) {
            DrawCircle(center_x, center_y, PointRadius, GREEN);
        }
    }
}

std::string Map::getMap() {
    return loaded_map;
}

bool Map::allExplored() const {
    return freeTileCount == exploredTileCount;
}



void Map::explore(const int x, const int y) {

    const int index = y * 50 + x;
    if (!explored_map[index] && loaded_map[index] == '0') {
        explored_map[index] = true;
        exploredTileCount++;
    }
}

void Map::explore(const int tile) {
    if (tile<0 || tile> loaded_map.size()) return;

    if (!explored_map[tile]&& loaded_map[tile] == '0') {
        explored_map[tile] = true;
        exploredTileCount++;
    }
}


bool Map::isExplored(const int x, const int y) const {
    if (x < 0 || x >= 50 || y < 0 || y >= 28) return false;
    return explored_map[y * 50 + x];
}

bool Map::canMove(const int tileNumber) const {
    if (tileNumber < 0 || tileNumber >= static_cast<int>(loaded_map.size()))
        return false;

    return loaded_map[tileNumber] == '0';

}

