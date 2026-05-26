#include <Arduino.h>
#include <constants.hpp>
#include <serial_input.hpp>

bool newMessage;
bool newTokens;
Token tokens[MAX_TOKENS];

void recvChars();
bool isFloatDigit(char c);
void tokenizer(char characters[], Token* out);
void parseTokens(Token inputTokens[]);

char receivedChars[MAX_MESSAGE_LENGTH];

void takeInput() {
  recvChars();
  if(newMessage == true)
  {
    tokenizer(receivedChars, tokens);
    newMessage = false;
    newTokens = true;
  }
}

void recvChars() {
  if (Serial.available() == 0) return;
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

bool isFloatDigit(char c) {
  if(isDigit(c) || c == '-' || c == '.') 
    return true;
  return false;
}

void tokenizer(char inputChars[], Token* outTokens) {
  int t = 0;
  int i = 0;
  while(inputChars[i] != '\0')
  {
    char currentChar = inputChars[i];

    // Command
    if (isAlpha(currentChar))
    {
      int j = 0;
      while(isAlpha(inputChars[i])) {
        outTokens[t].value.string[j++] = inputChars[i++];
      }
      outTokens[t].value.string[j] = '\0';
      outTokens[t].datatype = Datatype::COMMAND;
      
    }

    // Subcommand and Prefix
    else if(currentChar == ' ' && isAlpha(inputChars[++i]))
    {
      if(isFloatDigit(inputChars[i+1]))
      {
        outTokens[t].datatype = Datatype::PREFIX;
        outTokens[t].value.character = inputChars[i];
        i++;
      }
      else if(isAlpha(inputChars[i+1]))
      {
      int j = 0;
      while(isAlpha(inputChars[i])) {
        outTokens[t].value.string[j++] = inputChars[i++];
      }
      outTokens[t].value.string[j] = '\0';
      outTokens[t].datatype = Datatype::SUBCOMMAND;
      }
    }

    // Numbers
    else if(isFloatDigit(currentChar)) {
      char rawNumber[MAX_MESSAGE_LENGTH];
      int j = 0;
      while(isFloatDigit(inputChars[i])) {
        rawNumber[j++] = inputChars[i++];
      }
      rawNumber[j] = '\0';
      outTokens[t].datatype = Datatype::VALUE;
      outTokens[t].value.number = atof(rawNumber);
    }

    // Operators
    else if(!isAlpha(currentChar) && !isFloatDigit(currentChar)) {
      outTokens[t].datatype = Datatype::OPERATOR;
      outTokens[t].value.character = currentChar;
      t++;
      i++;
    }

    else {i++;}

    t++;
  }
  tokens[t].datatype = Datatype::OPERATOR;
  tokens[t].value.character = '\0';
}