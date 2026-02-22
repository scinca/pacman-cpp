//
// Created by simon on 22.02.26.
//

#include "map.h"

#include <fstream>

#include "config.h"
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
        if (loaded_map.length() != 1400) {
            return std::unexpected("Error loading Map, Map doesn't fit into the grid. Current Length:" + std::to_string(loaded_map.length()));
        }

        if (file.fail() && !file.eof()) {
            return std::unexpected("Error reading file: " + filename);
        }

        return {};

    }





    void Map::draw() const {
    for (std::int32_t i = 0; i < loaded_map.size(); i++) {
        const std::int32_t tile_x = (i % 50) * TileWidth + WindowConfig::WindowRoot;
        const std::int32_t tile_y = (i / 50) * TileWidth + WindowConfig::WindowRoot;

        if (loaded_map[i] == '#') {
            DrawRectangle(tile_x, tile_y, TileWidth, TileWidth, RAYWHITE);
        }
    }
}





