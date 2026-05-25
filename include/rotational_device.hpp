#pragma once

#include <Servo.h>
#include <gab_timer.hpp>

 
class RotationalDevice {
public:
    virtual void step() = 0;
    float getCurrentPosition();
    void setTargetPosition(float position);
    void setTimePeriod(int timePeriod);
    
protected:
    int targetPosition;
    int currentPosition;
    Timer timer;
};