#pragma once

#include <Servo.h>
#include <gab_timer.hpp>
#include <rotational_device.hpp>
 
class GabServo: public RotationalDevice {
public:
    GabServo();

    void attach(int pin);

    void step() override;
    
private:
    Servo servo;
};