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
    int GameMapWidth;
    int GameMapHeight;
    int GameMapRootX;
    int GameMapRootY;
    int TilesX = 50;
    int TilesY = 28;

    float TileWidth;
    float PointRadius;
    int FailurePercentage { 5 };
    int FontSize;
    int FontSizeSmall;
    float ButtonWidth;
    float ButtonHeight;
    float ButtonSpacing;
    float ButtonY = 20;
    float Velocity;
    float Margin;


private:
    std::string window_title_ {" Pacman Raylib Game"};
    int screen_width_;
    int screen_height_;
    ApplicationConfig();
    ~ApplicationConfig();

};


#endif //PACMAN_CPP_CONFIG_H
