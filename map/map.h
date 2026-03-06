//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_MAP_H
#define PACMAN_CPP_MAP_H
#include <expected>
#include <string>
#include <vector>


class Map {
    public:
    std::expected<void, std::string> load(const std::string& filename);
    void draw() const;
    std::string getMap();
    [[nodiscard]] bool allExplored() const;
    void explore(int x, int y);

    [[nodiscard]] bool isExplored(int x, int y) const;

private:
    std::string loaded_map;
    std::vector<bool> explored_map;
    int freeTileCount = 0;
    int exploredTileCount = 0;

};


#endif //PACMAN_CPP_MAP_H