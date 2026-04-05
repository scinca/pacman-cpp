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
    int failure_percentage { 15 };
    int font_size;
    int font_size_small;
    float button_width;
    float button_height;
    float button_spacing;
    float button_y = 20;
    float velocity_;
    float margin_;


private:
    std::string window_title_ {" Pacman Raylib Game"};
    int screen_width_;
    int screen_height_;
    ApplicationConfig();
    ~ApplicationConfig();

};


#endif //PACMAN_CPP_CONFIG_H
