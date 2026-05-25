#pragma once

#include <Servo.h>
#include <gab_timer.hpp>

 
class GabServo {
public:
    GabServo(int pin);

    float getCurrentPosition();
    void setTargetPosition(float position);
    void setTimePeriod(int timePeriod);
    void step();
    
private:
    int targetPosition;
    int currentPosition;
    Servo servo;
    Timer timer;
};