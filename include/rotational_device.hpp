#pragma once

#include <Servo.h>
#include <gab_timer.hpp>

 
class RotationalDevice {
public:
    virtual void step();
    float getCurrentPosition();
    void setTargetPosition(float position);
    void setTimePeriod(int timePeriod);
    
protected:
    int targetPosition;
    int currentPosition;
    Timer timer;
};