//
// Created by simon on 28.03.26.
//

#ifndef PACMAN_CPP_CONFIG_H
#define PACMAN_CPP_CONFIG_H
#include <cstdint>
#include <string>



class ApplicationConfig {
public:
    static ApplicationConfig& GetInstance() {
        static ApplicationConfig instance;
        return instance;
    }
    ApplicationConfig(const ApplicationConfig&) = delete;
    ApplicationConfig& operator=(const ApplicationConfig&) = delete;


    std::int32_t WindowRoot { 1 };
    std::int32_t GameMapWidth { 1601}; //50 tiles
    std::int32_t GameMapHeight = { 1001 }; // 28 tiles
    std::int32_t GameMapRootX { 1 };
    std::int32_t GameMapRootY { 101 };

    std::int32_t TileWidth { 32 };
    float PointRadius = TileWidth * 0.8 / 2;

    int failure_percentage { 15 };
    int font_size { 40 };

private:
    std::string window_title_ = "Raylib Pacman Game";
    int screen_width_;
    int screen_height_;
    ApplicationConfig();
    ~ApplicationConfig();

};


#endif //PACMAN_CPP_CONFIG_H
