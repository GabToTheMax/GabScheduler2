#pragma once

#include <Servo.h>
#include <gab_timer.hpp>

 
class RotationalDevice {
public:
    virtual void step() = 0;
    virtual void setTargetPosition(float position);
    float getCurrentPosition();
    void setTimePeriod(int timePeriod);
    void setEnabled(bool status);
    
protected:
    int targetPosition;
    int currentPosition;
    Timer timer;
};