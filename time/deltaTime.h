//
// Created by simon on 06.03.26.
//

#ifndef PACMAN_CPP_DELTATIME_H
#define PACMAN_CPP_DELTATIME_H


class Time {
private:
    double delta_time_{};
    double last_time_{};

    public:
    Time();
    [[nodiscard]] double GetDeltaTime() const;
    void CalculateDeltaTime();

};


#endif //PACMAN_CPP_DELTATIME_H
