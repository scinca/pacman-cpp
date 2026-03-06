//
// Created by simon on 06.03.26.
//

#ifndef PACMAN_CPP_DELTATIME_H
#define PACMAN_CPP_DELTATIME_H


class Time {
private:
    double deltaTime{};
    double lastTime{};
    void calculateDeltaTime();
    public:
    Time();
    [[nodiscard]] double getDeltaTime();

};


#endif //PACMAN_CPP_DELTATIME_H
