//
// Created by simon on 06.03.26.
//

#include "DeltaTime.h"



Time::Time() {
   delta_time_= 0.0f;
   last_time_ = std::chrono::steady_clock::now();
}


void Time::CalculateDeltaTime() {
   if (!running_) {
      delta_time_ = 0.0f;
      return;
   }

   const auto current_time = std::chrono::steady_clock::now();
   delta_time_ = std::chrono::duration<float, std::chrono::seconds::period>(current_time- last_time_).count();
   last_time_ = current_time;

}

float Time::GetDeltaTime() const {
   return delta_time_;
}


void Time::StartGameTimer() {
   last_time_ = std::chrono::steady_clock::now();
   running_ = true;

}