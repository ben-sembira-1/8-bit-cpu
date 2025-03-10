#include <AUnit.h>

test(getBase10DigitsDigitsOrder) {
  const int number = 123;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     3);
}

test(getBase10Digits4Digits) {
  const int number = 5678;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  6);
  assertEqual(digits.tens,      7);
  assertEqual(digits.units,     8);
}

test(getBase10Digits3Digits) {
  const int number = 125;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     5);
}

test(getBase10Digits2Digits) {
  const int number = 54;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  0);
  assertEqual(digits.tens,      5);
  assertEqual(digits.units,     4);
}

test(getBase10Digits1Digits) {
  const int number = 6;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     6);
}

test(getBase10DigitsZero) {
  const int number = 0;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hundreds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     0);
}

test(OutputEEPROMIsCorrectlyFlashed)
{
  setupPinModesForEEPROMReading();
  for (short number = 0; number < 256; number++)
  {
    EEPROMReading readingHundreds = readFromEEPROM(number);
    EEPROMReading readingTens = readFromEEPROM(number + 256);
    EEPROMReading readingUnits = readFromEEPROM(number + 512);
    assertEqual(readingHundreds.success, true);
    assertEqual(readingTens.success, true);
    assertEqual(readingUnits.success, true);
    int hundreds = number / 100;
    int tens = (number % 100) / 10;
    int units = number % 10;
    assertEqual(readingHundreds.data, commonAnodeSevenSegmentDisplayRepresentation(hundreds));
    assertEqual(readingTens.data, commonAnodeSevenSegmentDisplayRepresentation(tens));
    assertEqual(readingUnits.data, commonAnodeSevenSegmentDisplayRepresentation(units));

    Serial.println("Validated: " + String(number) + "/" + String(MAX_BYTE - 1));
  }
}
