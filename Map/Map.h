//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_MAP_H
#define PACMAN_CPP_MAP_H
#include <optional>
#include <string>
#include <vector>

#include "Database/Database.h"

enum class MapValidationError {
    InvalidLength,
    InvalidPlayerCount,
    InvalidEnemyCount,
    UnresolvableSymbols,
    CoinsUnreachable,
    DatabaseError,
    TooFewCoins,
};

class Map {
public:
    explicit Map(Database* db);
    Map(); // needed for the MapCreator

    void LoadMapFromDB(int map_number);
    void LoadFromString(const std::string &map);
    void Draw(bool editor = false) const;
    std::string GetMap();
    [[nodiscard]] bool AllExplored() const;
    void Explore(int tile);
    static std::pair<float, float> GetTileCenter(int tile) ;
    [[nodiscard]] bool CanMove(int tile) const;
    [[nodiscard]] int FindPlayerStartTile() const;
    [[nodiscard]] std::vector<int> FindEnemyStartTiles() const;



    static std::optional<MapValidationError> ValidateMap(const std::string& map);
    [[nodiscard]] int GetExploredTileCount() const {return score_;}
    [[nodiscard]] int GetFreeTileCount() const {return free_tile_count_;}
    static int GetTileFromXY(int x, int y);
private:
    Database* db_{};
    std::string loaded_map_;
    std::vector<bool> explored_map_;
    int free_tile_count_ = 0;
    int score_ = 0;
  };
#endif //PACMAN_CPP_MAP_H