#include <Arduino.h>
#include <serial_input.hpp>

void setup() {
  Serial.begin(9600);
}

void loop() {
  recvChars();
  Serial.println(receivedChars);
}