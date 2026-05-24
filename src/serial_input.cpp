#include <Arduino.h>
#include <constants.hpp>
#include <serial_input.hpp>

bool newMessage = false;
char receivedChars[MAX_MESSAGE_LENGTH];

void recvChars() {
  if (Serial.available() != 0) {
    int i = 0;
    while (newMessage == false) {
      bool newChar = false;
      char currentChar;


      while (newChar == false) {
        if (Serial.available() > 0) {
          currentChar = Serial.read();
          newChar = true;
        }
      }

      if (currentChar == END_CHAR) {
        receivedChars[i] = '\0';
        newMessage = true;
      } 
      else {
        receivedChars[i] = currentChar;
        i++;
        newChar = false;
        if (i == MAX_MESSAGE_LENGTH - 1) {
          receivedChars[i] = '\0';
          newMessage = true;
        }
      }
    }
  }
}