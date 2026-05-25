#include <Arduino.h>
#include <constants.hpp>
#include <serial_input.hpp>


void recvChars();
bool isFloatDigit(char c);
void tokenizer();

bool newMessage = false;
char receivedChars[MAX_MESSAGE_LENGTH];
Token tokens[MAX_TOKENS];

void takeInput() {
  recvChars();
  if(newMessage == true)
    tokenizer();
}

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

bool isFloatDigit(char c) {
  if(isDigit(c) || c == '-' || c == '.') 
    return true;
  return false;
}

void tokenizer() {
  int currentToken = 0;
  int i = 0;
  while(receivedChars[i] != END_CHAR)
  {
    char currentChar = receivedChars[i];

    // Command
    if (isAlpha(currentChar))
    {
      char command[MAX_MESSAGE_LENGTH];
      int j = 0;
      while(isAlpha(receivedChars[i])) {
        command[j++] = receivedChars[i++];
      }
      tokens[currentToken].datatype = Datatype::COMMAND;
      tokens[currentToken].value.string = command;
    }

    // Subcommand and Prefix
    else if(currentChar == ' ' && isAlpha(receivedChars[++i]))
    {
      if(isFloatDigit(receivedChars[i+1]))
      {
        tokens[currentToken].datatype = Datatype::PREFIX;
        tokens[currentToken].value.character = receivedChars[i];
      }
      else if(isAlpha(receivedChars[i+1]))
      {
        char subcommand[MAX_MESSAGE_LENGTH];
        int j = 0;
        while(isFloatDigit(receivedChars[i])) {
          subcommand[j++] = receivedChars[i++];
        }
        tokens[currentToken].datatype = Datatype::SUBCOMMAND;
        tokens[currentToken].value.string = subcommand;
      }
    }

    // Numbers
    else if(isFloatDigit(currentChar)) {
      char rawNumber[MAX_MESSAGE_LENGTH];
      int j = 0;
      while(isFloatDigit(receivedChars[i])) {
        rawNumber[j++] = receivedChars[i++];
      }
      tokens[currentToken].datatype = Datatype::VALUE;
      tokens[currentToken].value.number = atof(rawNumber);
    }

    // Operators
    else if(!isAlpha(currentChar) && !isFloatDigit(currentChar)) {
      tokens[currentToken].datatype = Datatype::OPERATOR;
      tokens[currentToken].value.character = currentChar;
      currentToken++;
      break;
    }

    else {i++;}

    currentToken++;
  }
  tokens[currentToken].datatype = Datatype::OPERATOR;
  tokens[currentToken].value.character = '\0';
}