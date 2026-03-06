//
// Created by simon on 22.02.26.
//

#ifndef PACMAN_CPP_CONFIG_H
#define PACMAN_CPP_CONFIG_H

namespace WindowConfig {
    inline constexpr std::int32_t WindowWidth { 1601}; //50 tiles
    inline constexpr std::int32_t WindowHeight = { 901 }; // 28 tiles
    inline constexpr std::int32_t WindowRoot { 1 };
    inline constexpr char WindowTitle[] { "Raylib Pacman Game"}; // C-Style string bc Raylib expects it.
}

inline constexpr std::int32_t TileWidth { 32 };

#endif //PACMAN_CPP_CONFIG_H