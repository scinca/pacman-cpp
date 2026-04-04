//
// Created by simon on 06.03.26.
//

#ifndef PACMAN_CPP_DELTATIME_H
#define PACMAN_CPP_DELTATIME_H
#include <chrono>




class Time {
public:
    explicit Time();
    [[nodiscard]] float GetDeltaTime() const;
    void CalculateDeltaTime();
    void StartGameTimer();
    void PauseGameTimer(){running_ = false;}
private:
    float delta_time_{};
    std::chrono::steady_clock::time_point last_time_{};
    bool running_{ false };


};


#endif //PACMAN_CPP_DELTATIME_H
