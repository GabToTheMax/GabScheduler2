#include <AccelStepper.h>
#include <gab_stepper.hpp>
#include <gab_timer.hpp>
#include <Arduino.h>

GabStepper::GabStepper() {
    timer.setTimePeriod(10);
    timer.setEnabled(false);
}

void GabStepper::init(int type, int step, int dir) {
    stepper = AccelStepper(type, step, dir);
    stepper.setMaxSpeed(800);
    stepper.setAcceleration(500);
    stepper.setCurrentPosition(0);
}

void GabStepper::setTargetPosition(float position) {
  targetPosition = position;
  stepper.moveTo((long)targetPosition);
}

void GabStepper::step()
{
    if (timer.canRun())
    {
        stepper.run();
        if (!stepper.isRunning())
            timer.setEnabled(false);
    }
}