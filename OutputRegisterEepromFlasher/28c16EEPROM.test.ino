#include <AUnit.h>

test(intArrayLengthHappyFlow) {
  const int testArray[] = {1, 2, 4};
  assertEqual(intArrayLength(testArray), 3);
}

test(intArrayLengthEmptyArray) {
  const int testArray[] = {};
  assertEqual(intArrayLength(testArray), 0);
}

test(EEPROMIsCorrectlyFlashed) {
  setupPinModesForEEPROMReading();
  for (short number = 0; number < 256; number++) {
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
