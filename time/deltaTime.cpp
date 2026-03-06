//
// Created by simon on 06.03.26.
//

#include "deltaTime.h"
#include <raylib.h>

Time::Time(){
   deltaTime= 0.0;
   lastTime = GetTime();
}


void Time::calculateDeltaTime() {
   const double currentTime { GetTime()};
   deltaTime = currentTime - lastTime;
   lastTime = currentTime;
}

double Time::getDeltaTime() {
   calculateDeltaTime();
   return deltaTime;
}
