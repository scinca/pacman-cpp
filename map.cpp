//
// Created by simon on 22.02.26.
//

#include "map.h"

#include <fstream>


class Map {
    public:
    std::expected<void, std::string> load(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return std::unexpected("Failed to open file: " + filename);
        }

        loaded_map.assign((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        std::erase(loaded_map, '\n'); //remove newline so for loop can draw map.
        std::erase(loaded_map, '\r'); // needed on windows

        if (file.fail() && !file.eof()) {
            return std::unexpected("Error reading file: " + filename);
        }

        return {};

    }



     private:
     std::string loaded_map;


};