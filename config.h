//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_CONFIG_H
#define PACMAN_CPP_CONFIG_H
#include <cstdint>
#include <raylib.h>

namespace WindowConfig {
    inline const std::int32_t ScreenWidth {GetScreenWidth()};
    inline const std::int32_t ScreenHeight {GetScreenHeight()};
    inline constexpr std::int32_t GameMapWidth { 1601}; //50 tiles
    inline constexpr std::int32_t GameMapHeight = { 1001 }; // 28 tiles
    inline constexpr std::int32_t GameMapRootX { 1 };
    inline constexpr std::int32_t GameMapRootY { 101 };
    inline constexpr std::int32_t WindowRoot { 1 };
    inline constexpr char WindowTitle[] { "Raylib Pacman Game"}; // C-Style string bc Raylib expects it.

}

inline constexpr std::int32_t TileWidth { 32 };
inline constexpr double PointRadius { TileWidth * 0.8 / 2 };

inline constexpr int failure_percentage { 15 };
inline constexpr int font_size { 40 };

#endif //PACMAN_CPP_CONFIG_H