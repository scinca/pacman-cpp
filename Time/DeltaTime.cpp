//
// Created by simon on 06.03.26.
//

#include "DeltaTime.h"

#include <algorithm>
#include <raylib.h>

Time::Time(){
   delta_time_= 0.0;
   last_time_ = GetTime();
}


void Time::CalculateDeltaTime() {
   const double currentTime { GetTime()};
   delta_time_ = currentTime - last_time_;
   delta_time_ = std::min(delta_time_, 0.05); // min value to make movement more smooth
   last_time_ = currentTime;
}

double Time::GetDeltaTime() const {
   return delta_time_;
}
