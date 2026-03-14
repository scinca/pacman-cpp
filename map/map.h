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
        void LoadDefaultMap();
        void Draw() const;
        std::string GetMap();
        [[nodiscard]] bool AllExplored() const;
        void Explore(int x, int y);
        void Explore(int tile);
        static std::pair<float, float> GetTileCenter(int tile) ;
        [[nodiscard]] bool IsExplored(int x, int y) const;
        [[nodiscard]] bool CanMove(int tileNumber) const;
        [[nodiscard]] int FindPlayerStartTile() const;
        [[nodiscard]] std::vector<int> FindEnemyStartTiles() const;



    private:
        std::string loaded_map_;
        std::vector<bool> explored_map_;
        int free_tile_count_ = 0;
        int explored_tile_count_ = 0;
        std::string default_map_ = "X000000000000000000000000000000000000000000?0000000###0###0#####0#####0########0#####0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###?###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0000#00000#0#000#0#0#0#####0###0###00###00000###0#0000000#0000#0#0000000#####00000###00###0#0#0###0#0000##0#00#0#0#0#0#0#0#####0###0###0000000000000000000000000000000000000000000000000000###0#0#0###0#0000#00000#0#000#0#0#0#####0###0###00###00000###0#0000000000000000000000#####00000###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###0000000000000000000000000000000000000000000000000000###0#0#0###0#0##0##0#0######0#####0#####0###0###00###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###0000000000000000000000000000000000000000000000000000###00000###0#0000000#0######0000000#####00000###00###0#0#0###0#0##0##0#0######0#####0#####0###0###000000000000000000000000000000000000000000000000000";
};


#endif //PACMAN_CPP_MAP_H