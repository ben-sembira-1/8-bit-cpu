#include <AUnit.h>

byte commonAnodeSevenSegmentDisplayRepresentation(byte digit) {
  const byte SEVEN_SEGMENT_DISPLAY_DIGITS[10] = {
    //ABCDEFG(RDP)
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

struct Base10Digits {
  byte hundreds = 0;
  byte tens = 0;
  byte units = 0;
};

struct EEPROMReading {
  byte data;
  bool success;
};

struct Base10Digits getBase10Digits(int number) {
  Base10Digits digits;
  digits.hundreds = ( number / 100) % 10;
  digits.tens     = ( number / 10)  % 10;
  digits.units    =   number        % 10;
  return digits;
}

void flashNumberDigits(byte number) {
    Base10Digits digits = getBase10Digits(number);
    writeToEEPROM(number, commonAnodeSevenSegmentDisplayRepresentation(digits.hundreds));
    writeToEEPROM(number + pow(2, 8), commonAnodeSevenSegmentDisplayRepresentation(digits.tens));
    writeToEEPROM(number + pow(2, 9), commonAnodeSevenSegmentDisplayRepresentation(digits.units));
}

void flashAll8BitNumbersDigits() {
  const int MAX_BYTE = pow(2, 8);
  for (int number = 0; number < MAX_BYTE; number++) {
    flashNumberDigits(number);
    Serial.println("Flashed " + String(number + 1) + "/" + String(MAX_BYTE) + " numbers.");
  }
}


void debugFlashOneNumberAndWait(short address, byte data) {
  if (writeToEEPROM(address, data)) {
    Serial.println("Successfully wrote " + String(data) + " to address 1111111111");
  } else {
    Serial.println("Error in writing a single value");
  }
}

void setup() {
  Serial.begin(9600);

  setupPinModesForEEPROMWriting();
  debugFlashOneNumberAndWait(2047, 0b01010101);

  setupPinModesForEEPROMReading();
  EEPROMReading reading = readFromEEPROM(2047);
  Serial.println("Data read from the EEPROM: " + String(reading.success) + " - " + String(reading.data));

  // flashAll8BitNumbersDigits();

  Serial.println("===============================");
  Serial.println("Finished flashing successfully!");
  Serial.println("===============================");
}

void loop() {
  aunit::TestRunner::run();
}
