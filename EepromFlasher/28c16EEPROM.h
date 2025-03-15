#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include "utils.h"

const int ADDRESS_PINS[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42};
const int IO_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};
const int WRITE_ENABLE_PIN = 48;
const int OUTPUT_ENABLE_PIN = 50;
const int CHIP_ENABLE_PIN = 52;

const int CHIP_MAX_HOLD_TIME_MILLISECONDS = 1;

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

struct EEPROMReading
{
	byte data;
	bool success;
};

bool writeToEEPROM(short address, byte data);
struct EEPROMReading readFromEEPROM(short address);
void setupPinModesForEEPROMWriting();
void setupPinModesForEEPROMReading();

#endif