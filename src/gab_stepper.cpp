#include <AccelStepper.h>
#include <gab_stepper.hpp>
#include <gab_timer.hpp>
#include <Arduino.h>

GabStepper::GabStepper(int type, int step, int dir) {
    stepper = AccelStepper(type, step, dir);
    stepper.setMaxSpeed(800);
    stepper.setAcceleration(500);
    stepper.setCurrentPosition(0);

    timer.setTimePeriod(1);
    timer.setEnabled(false);
}

void GabStepper::setTargetPosition(float position) {
  targetPosition = position;
  stepper.moveTo(targetPosition);
}

void GabStepper::step()
{
    if (timer.canRun())
    {
        stepper.run();
        if (!stepper.isRunning())
            timer.setEnabled(false);

        Serial.print("J1 ");
        Serial.println(stepper.currentPosition());
    }
}