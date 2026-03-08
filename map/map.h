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
    std::expected<void, std::string> Load(const std::string& filename);
    void Draw() const;
    std::string GetMap();
    [[nodiscard]] bool AllExplored() const;
    void Explore(int x, int y);
    void Explore(int tile);
    static std::pair<float, float> GetTileCenter(int tile) ;
    [[nodiscard]] bool IsExplored(int x, int y) const;
    [[nodiscard]] bool CanMove(int tileNumber) const;



private:
    std::string loaded_map_;
    std::vector<bool> explored_map_;
    int free_tile_count_ = 0;
    int explored_tile_count_ = 0;
};


#endif //PACMAN_CPP_MAP_H