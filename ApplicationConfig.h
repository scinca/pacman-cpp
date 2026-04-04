//
// Created by simon on 28.03.26.
//

#ifndef PACMAN_CPP_CONFIG_H
#define PACMAN_CPP_CONFIG_H
#include <string>


class ApplicationConfig {
public:
    static ApplicationConfig& GetInstance() {
        static ApplicationConfig instance;
        return instance;
    }
    ApplicationConfig(const ApplicationConfig&) = delete;
    ApplicationConfig& operator=(const ApplicationConfig&) = delete;


    int WindowRoot { 1 };
    int GameMapWidth { 1601}; //50 tiles
    int GameMapHeight = { 1001 }; // 28 tiles
    int GameMapRootX;
    int GameMapRootY;
    int TilesX = 50;
    int TilesY = 28;

    float TileWidth;
    float PointRadius;

    int failure_percentage { 15 };
    int font_size { 40 };

private:
    std::string window_title_ {" Pacman Raylib Game"};
    int screen_width_;
    int screen_height_;
    ApplicationConfig();
    ~ApplicationConfig();

};


#endif //PACMAN_CPP_CONFIG_H
