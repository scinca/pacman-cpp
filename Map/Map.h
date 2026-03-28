//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_MAP_H
#define PACMAN_CPP_MAP_H
#include <expected>
#include <string>
#include <vector>

#include "../Database/Database.h"


class Map {
public:
    explicit Map(Database* db);
    std::expected<void, std::string> LoadMapFromDB(int map_number);
    void Draw() const;
    std::string GetMap();
    [[nodiscard]] bool AllExplored() const;
    void Explore(int tile);
    static std::pair<float, float> GetTileCenter(int tile) ;
    [[nodiscard]] bool IsExplored(int x, int y) const;
    [[nodiscard]] bool CanMove(int tileNumber) const;
    [[nodiscard]] int FindPlayerStartTile() const;
    [[nodiscard]] std::vector<int> FindEnemyStartTiles() const;
    static bool ValidateMap(const std::string& map);

private:
    Database* database_;
    std::string loaded_map_;
    std::vector<bool> explored_map_;
    int free_tile_count_ = 0;
    int explored_tile_count_ = 0;
  };
#endif //PACMAN_CPP_MAP_H