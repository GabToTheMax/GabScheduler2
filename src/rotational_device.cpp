#include <rotational_device.hpp>
#include <gab_timer.hpp>

void RotationalDevice::setTimePeriod(int timePeriod) {
    timer.setTimePeriod(timePeriod);
}

float RotationalDevice::getCurrentPosition() {
    return currentPosition;
}

void RotationalDevice::setTargetPosition(float position) {
    targetPosition = position;
}
