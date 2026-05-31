#include <parse_input.hpp>
#include <rotational_device.hpp>
#include <serial_input.hpp>
#include <Arduino.h>

void MVL(Token inputTokens[], RotationalDevice** devices);

void DetectCommand(Token inputTokens[], RotationalDevice** devices) {
    char* command;
    for(int i = 0; i < MAX_TOKENS; i++) {
        if(inputTokens[i].datatype == Datatype::COMMAND) 
        {
            command = inputTokens[i].value.string;
            break;
        }
        return;
    }
    if(strcmp(command, "MVL") == 0) { MVL(inputTokens, devices); }
}

int PrefixToDevice(char c) {
    switch(c)
    {
        case 'T': return 0;
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'D': return 4;
        case 'E': return 5;
        case 'F': return 6;
        default: return -1;
    }
}

void MVL(Token inputTokens[], RotationalDevice** devices) {
    // Serial.println("Detected MVL");
    int i = 0; 
    while(i < MAX_TOKENS) {
        Serial.println(i);
        if(inputTokens[i].datatype != Datatype::PREFIX) {i++; continue;}
        if(inputTokens[i+1].datatype != Datatype::VALUE) {i++; continue;}
        char prefix = inputTokens[i].value.character;
        int position = inputTokens[i+1].value.number;
        devices[PrefixToDevice(prefix)]->setTargetPosition(position);
        devices[PrefixToDevice(prefix)]->setEnabled(true);
        Serial.print("set ");
        Serial.println(prefix);
        i += 2;
    }
}