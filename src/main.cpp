#include <Arduino.h>
#include <serial_input.hpp>
#include <gab_stepper.hpp>
#include <gab_servo.hpp>
#include <constants.hpp>

GabServo TH(TOOL_PIN);
GabStepper J1(1, J1_STEP, J1_DIR);
RotationalDevice* devices[2] = 
{
  &TH, 
  &J1
};

void setup() {
  Serial.begin(9600);
}

int counterThing = 0;

void loop() {
  Serial.print(counterThing++);
  Serial.println("test");
  takeInput();
  for(int i = 0; i < MAX_TOKENS; i++)
  {
    Serial.print((int)tokens[i].datatype);
    switch (tokens[i].datatype)
    {
    case Datatype::OPERATOR:
      Serial.print(tokens[i].value.character);
      break;

    case Datatype::COMMAND:
      Serial.print(tokens[i].value.string);
      break;

    case Datatype::SUBCOMMAND:
      Serial.print(tokens[i].value.string);
      break;

    case Datatype::PREFIX:
      Serial.print(tokens[i].value.character);
      break;
  
    case Datatype::VALUE:
      Serial.print(tokens[i].value.number);
      break;

    default:
      break;
    }
    Serial.println();
  }

  for(int i = 0; i < DEVICES_COUNT; i++)
  {
    devices[i]->step();
  }
}