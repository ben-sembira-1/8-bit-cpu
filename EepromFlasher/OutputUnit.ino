#include <AUnit.h>

#define MAX_BYTE (256)

byte commonAnodeSevenSegmentDisplayRepresentation(byte digit)
{
  const byte SEVEN_SEGMENT_DISPLAY_DIGITS[10] = {
      // ABCDEFG(RDP)
      0b11111100,
      0b01100000,
      0b11011010,
      0b11110010,
      0b01100110,
      0b10110110,
      0b10111110,
      0b11100000,
      0b11111110,
      0b11100110,
  };

  byte invertedRepresentation = SEVEN_SEGMENT_DISPLAY_DIGITS[digit] ^ 0b11111111;
  return invertedRepresentation;
}

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

struct Base10Digits
{
  byte hundreds = 0;
  byte tens = 0;
  byte units = 0;
};


struct Base10Digits getBase10Digits(int number)
{
  Base10Digits digits;
  digits.hundreds = (number / 100) % 10;
  digits.tens = (number / 10) % 10;
  digits.units = number % 10;
  return digits;
}

void flashNumberDigits(byte number)
{
  Base10Digits digits = getBase10Digits(number);
  writeToEEPROM(number, commonAnodeSevenSegmentDisplayRepresentation(digits.hundreds));
  writeToEEPROM(number + pow(2, 8), commonAnodeSevenSegmentDisplayRepresentation(digits.tens));
  writeToEEPROM(number + pow(2, 9), commonAnodeSevenSegmentDisplayRepresentation(digits.units));
}

void flashAll8BitNumbersDigits()
{
  const int LOG_INTERVAL = 50;
  for (int number = 0; number < MAX_BYTE; number++)
  {
    flashNumberDigits(number);
    if ((number + 1) % LOG_INTERVAL == 0)
    {
      Serial.println("Flashed: " + String(number + 1) + "/" + String(MAX_BYTE));
    }
  }
  Serial.println("Successfully flashed " + String(MAX_BYTE) + " numbers.\n");
}

void redPrintln(String s)
{
  Serial.println("\033[31m" + s + "\033[0m");
}

void greenPrintln(String s)
{
  Serial.println("\033[32m" + s + "\033[0m");
}

bool validateSingleNumber(short number)
{
  EEPROMReading readingHundreds = readFromEEPROM(number);
  EEPROMReading readingTens = readFromEEPROM(number + 256);
  EEPROMReading readingUnits = readFromEEPROM(number + 512);
  int hundreds = number / 100;
  int tens = (number % 100) / 10;
  int units = number % 10;
  return (
      readingHundreds.success &&
      readingTens.success &&
      readingUnits.success &&
      readingHundreds.data == commonAnodeSevenSegmentDisplayRepresentation(hundreds) &&
      readingTens.data == commonAnodeSevenSegmentDisplayRepresentation(tens) &&
      readingUnits.data == commonAnodeSevenSegmentDisplayRepresentation(units));
}

void validateOutputEeprom()
{
  Serial.println(">>> Validating Output Unit <<<");
  setupPinModesForEEPROMReading();
  const int LOG_INTERVAL = 50;
  for (short number = 0; number < 256; number++)
  {
    if (!validateSingleNumber(number))
    {
      redPrintln("Error: The number " + String(number) + " did not flash correctly.");
      return;
    }

    if ((number + 1) % LOG_INTERVAL == 0)
    {
      Serial.println("Validated: " + String(number + 1) + "/" + String(MAX_BYTE - 1));
    }
  }
  greenPrintln("Successfully validated all 256 numbers.\n");
}
