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
    Map();

    std::expected<void, std::string> LoadMapFromDB(int map_number);
    void Draw(bool editor = false) const;
    std::string GetMap();
    [[nodiscard]] bool AllExplored() const;
    void Explore(int tile);
    static std::pair<float, float> GetTileCenter(int tile) ;
    [[nodiscard]] bool CanMove(int tileNumber) const;
    [[nodiscard]] int FindPlayerStartTile() const;
    [[nodiscard]] std::vector<int> FindEnemyStartTiles() const;

    void LoadFromString(const std::string &map);

    static bool ValidateMap(const std::string& map);
    [[nodiscard]] int GetExploredTileCount() const {return explored_tile_count_;}
    [[nodiscard]] int GetFreeTileCount() const {return free_tile_count_;}

    static int GetTileFromXY(int x, int y);
private:
    Database* db_{};
    std::string loaded_map_;
    std::vector<bool> explored_map_;
    int free_tile_count_ = 0;
    int explored_tile_count_ = 0;
  };
#endif //PACMAN_CPP_MAP_H