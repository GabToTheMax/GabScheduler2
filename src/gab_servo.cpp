#include <Servo.h>
#include <gab_servo.hpp>
#include <gab_timer.hpp>
#include <Arduino.h>
#include <constants.hpp>

GabServo::GabServo(int pin) {
    servo.attach(pin);
    timer.setTimePeriod(10);
    currentPosition = 0;
    targetPosition = 0;                                                                                                                                                                                         
    servo.write(0);
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

        //Serial.print(TOOL_PIN);
        //Serial.print("Tool ");
        Serial.println(servo.read());
    }
}
    
// private:
//     int targetPosition;
//     int currentPosition;
//     Servo servo;
//     Timer timer;
// };