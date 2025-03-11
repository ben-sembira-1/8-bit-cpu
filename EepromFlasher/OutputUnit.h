#ifndef OUTPUTUNIT_H
#define OUTPUTUNIT_H

#include "28c16EEPROM.h"

struct Base10Digits
{
	byte hundreds = 0;
	byte tens = 0;
	byte units = 0;
};

byte commonAnodeSevenSegmentDisplayRepresentation(byte digit);
struct Base10Digits getBase10Digits(int number);
void flashAll8BitNumbersDigits();
void validateOutputEeprom();

#endif