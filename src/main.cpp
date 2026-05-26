#include <Arduino.h>
#include <serial_input.hpp>
#include <gab_stepper.hpp>
#include <gab_servo.hpp>
#include <constants.hpp>

void tokenPrinter(Token inputTokens[]);

GabServo TH(TOOL_PIN);
GabStepper J1(1, J1_STEP, J1_DIR);
RotationalDevice* devices[2] = 
{
  &TH, 
  &J1
};

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("<Active>");
}

void loop() {
  takeInput();
  if(newTokens)
  {
    tokenPrinter(tokens);
    newTokens = false;
  }

  for(int i = 0; i < DEVICES_COUNT; i++)
  {
    devices[i]->step();
  }
}

void tokenPrinter(Token inputTokens[]) {
  for(int i = 0; i < MAX_TOKENS; i++)
  {
    switch (inputTokens[i].datatype)
    {
    case Datatype::OPERATOR:
      Serial.print("OPERATOR ");
      Serial.print(inputTokens[i].value.character);
      break;

    case Datatype::COMMAND:
      Serial.print("COMMAND ");
      Serial.print(inputTokens[i].value.string);
      break;

    case Datatype::SUBCOMMAND:
      Serial.print("SUBCOMMAND ");
      Serial.print(inputTokens[i].value.string);
      break;

    case Datatype::PREFIX:
      Serial.print("PREFIX ");
      Serial.print(inputTokens[i].value.character);
      break;
  
    case Datatype::VALUE:
      Serial.print("VALUE ");
      Serial.print(inputTokens[i].value.number);
      break;

    default:
      break;
    }
    Serial.println();
  }

}