#include <Arduino.h>
#include <gab_timer.hpp>

Timer::Timer() {
  previousRunTime = 0;
  timePeriod = 0; 
  enabled = false;
}

void Timer::setTimePeriod(int t) {
  timePeriod = t;
}

void Timer::setEnabled(bool e) {
  enabled = e;
}

bool Timer::canRun() {
  int currentTime = millis();
  if(currentTime-previousRunTime > timePeriod && enabled)
  {
    // if(previousRunTime+2*timePeriod > currentTime)
    //   previousRunTime = currentTime;
    // else
    //   previousRunTime += currentTime;
    
    previousRunTime = currentTime;
    return true;
  }
  return false;
}