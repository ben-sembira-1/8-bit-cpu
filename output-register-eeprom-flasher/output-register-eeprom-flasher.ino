#include <AUnit.h>

const int ADDRESS_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int IO_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int CHIP_ENABLE_PIN = 11;
const int OUTPUT_ENABLE_PIN = 12;
const int WRITE_ENABLE_PIN = 13;

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

void setPinsToModeOutput(int pins[]) {
  for (int i = 0; i < intArrayLength(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }
}

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

struct Base10Digits {
  byte hunderds = 0;
  byte tens = 0;
  byte units = 0;
};

struct Base10Digits getBase10Digits(int number) {
  Base10Digits digits;
  digits.hunderds = ( number / 100) % 10;
  digits.tens     = ( number / 10)  % 10;
  digits.units    =   number        % 10;
  return digits;
}

void writeToEEPROM(short address, byte data) {
  const short MAX_EEPROM_ADDRESS = 2^11 - 1;
  if (address > MAX_EEPROM_ADDRESS) {
    return;
  }
}

void flashNumberDigits(byte number) {
    Base10Digits digits = getBase10Digits(number);
    writeToEEPROM(number, SEVEN_SEGMENT_DISPLAY_DIGITS[digits.hunderds]);
    writeToEEPROM(number + 2^8, SEVEN_SEGMENT_DISPLAY_DIGITS[digits.tens]);
    writeToEEPROM(number + 2^9, SEVEN_SEGMENT_DISPLAY_DIGITS[digits.units]);
}

void setupAllOutputPins() {
  setPinsToModeOutput(ADDRESS_PINS);
  setPinsToModeOutput(IO_PINS);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  setPinsToModeOutput(ENABLE_PINS);
}

void flashAll8BitNumbersDigits() {
  const int MAX_BYTE = 2^8;
  for (int number = 0; number < MAX_BYTE; number++) {
    flashNumberDigits(number);
  }
}

void setup() {
  Serial.begin(9600);

  setupAllOutputPins();
  flashAll8BitNumbersDigits();
}

void loop() {
  // put your main code here, to run repeatedly:
  aunit::TestRunner::run();
}
















// -------------------- Tests --------------------

test(intArrayLengthHappyFlow) {
  const int testArray[] = {1, 2, 4};
  assertEqual(intArrayLength(testArray), 3);
}

test(intArrayLengthEmptyArray) {
  const int testArray[] = {};
  assertEqual(intArrayLength(testArray), 0);
}

test(getBase10DigitsDigitsOrder) {
  const int number = 123;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     3);
}

test(getBase10Digits4Digits) {
  const int number = 5678;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  6);
  assertEqual(digits.tens,      7);
  assertEqual(digits.units,     8);
}

test(getBase10Digits3Digits) {
  const int number = 125;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     5);
}

test(getBase10Digits2Digits) {
  const int number = 54;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      5);
  assertEqual(digits.units,     4);
}

test(getBase10Digits1Digits) {
  const int number = 6;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     6);
}

test(getBase10DigitsZero) {
  const int number = 0;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     0);
}
