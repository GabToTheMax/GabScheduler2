#pragma once

#include <constants.hpp>

union Value {
  char* string;
  char character;
  float number;
};

enum class Datatype {
  COMMAND,
  SUBCOMMAND,
  PREFIX,
  VALUE,
  OPERATOR
};

struct Token {
  Datatype datatype;
  Value value;
};

extern Token tokens[MAX_TOKENS];

void takeInput();