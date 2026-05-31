#include <Servo.h>
#include <gab_servo.hpp>
#include <gab_timer.hpp>
#include <Arduino.h>
#include <constants.hpp>

GabServo::GabServo() {
    timer.setTimePeriod(10);
    currentPosition = 0;
    targetPosition = 0;                                                                                                                                                                                         
    servo.write(0);
}

void GabServo::attach(int pin) {
    servo.attach(pin);
}

void GabServo::step() {
    if(timer.canRun()) {
        if(currentPosition > targetPosition)
        {
        currentPosition--;
        }
        else if(currentPosition < targetPosition)
        {
        currentPosition++;
        }
        if(currentPosition == targetPosition)
        {
        timer.setEnabled(false);
        }

        servo.write(currentPosition);

        Serial.print("T ");
        Serial.println(servo.read());
    }
}
