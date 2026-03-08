//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_MAP_H
#define PACMAN_CPP_MAP_H
#include <expected>
#include <string>
#include <vector>

/*
 * Map class contains following:
 * load() loads the map from filename
 * draw() Draws the Map ( and score)
 * getMap() returns the loaded_map string ( Currently unused).
 * explore() will handle the score, method is called on player move
 * allExplored() checks if game is done
 * isExplored() is a helper that checks whether a tile is explored. Used by draw()
 */

class Map {
    public:
    std::expected<void, std::string> load(const std::string& filename);
    void draw() const;
    std::string getMap();
    [[nodiscard]] bool allExplored() const;
    void explore(int x, int y);
    void explore(int tile);

    [[nodiscard]] bool isExplored(int x, int y) const;
    [[nodiscard]] bool canMove(int tileNumber) const;



private:
    std::string loaded_map;
    std::vector<bool> explored_map;
    int freeTileCount = 0;
    int exploredTileCount = 0;
};


#endif //PACMAN_CPP_MAP_H