#pragma once

#include <AccelStepper.h>
#include <gab_timer.hpp>
#include <rotational_device.hpp>
#include <constants.hpp>
 
class GabStepper: public RotationalDevice {
public:
    GabStepper(int type, int step, int dir);

    void setTargetPosition(float position) override;
    void step() override;
    
private:
    AccelStepper stepper;
};