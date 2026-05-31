#pragma once

#include <AccelStepper.h>
#include <gab_timer.hpp>
#include <rotational_device.hpp>
#include <constants.hpp>
 
class GabStepper: public RotationalDevice {
public:
    GabStepper();

    void setTargetPosition(float position) override;
    void init(int type, int step, int dir);
    void step() override;
    
private:
    AccelStepper stepper;
};