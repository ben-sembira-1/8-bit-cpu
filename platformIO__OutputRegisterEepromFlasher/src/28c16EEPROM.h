#include <Arduino.h>

bool writeToEEPROM(short address, byte data);

byte readFromEEPROM(short address);

void setupPinModesForEEPROMWriting();

void setupPinModesForEEPROMReading();
