#include <Arduino.h>
#include <AUnit.h>

const int ADDRESS_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int IO_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int WRITE_ENABLE_PIN = 11;
const int OUTPUT_ENABLE_PIN = 12;
const int CHIP_ENABLE_PIN = 13;

const int CHIP_MAX_HOLD_TIME_MICROSECONDS = 1;

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

void pinArrayMode(int pins[], int mode) {
  for (int i = 0; i < intArrayLength(pins); i++) {
    pinMode(pins[i], mode);
  }
}

void enableChip() {
  digitalWrite(CHIP_ENABLE_PIN, LOW);
}

void disableChip() {
  digitalWrite(CHIP_ENABLE_PIN, HIGH);
}

void enableWrite() {
  digitalWrite(WRITE_ENABLE_PIN, LOW);
}

void disableWrite() {
  digitalWrite(WRITE_ENABLE_PIN, HIGH);
}

void enableOutput() {
  digitalWrite(OUTPUT_ENABLE_PIN, LOW);
}

void disableOutput() {
  digitalWrite(OUTPUT_ENABLE_PIN, HIGH);
}

bool setAddress(short address) {
  const byte ADDRESS_BITS = 11;
  const short MAX_ADDRESS = pow(2, ADDRESS_BITS) - 1;
  if (address > MAX_ADDRESS) {
    Serial.println("The address: " + String(address) + "is too big. The max address alowed is " + String(MAX_ADDRESS));
    return false;
  }
  for (byte address_bit_number = 0; address_bit_number < ADDRESS_BITS; address_bit_number++) {
    bool bit_value = bitRead(address, address_bit_number);
    int bit_pin = ADDRESS_PINS[address_bit_number];
    digitalWrite(bit_pin, bit_value);
  }
  return true;
}

void setData(byte data) {
  byte DATA_BITS_COUNT = 8;
  for (byte data_bit_number = 0; data_bit_number < DATA_BITS_COUNT; data_bit_number++) {
    bool bit_value = bitRead(data, data_bit_number);
    int bit_pin = IO_PINS[data_bit_number];
    digitalWrite(bit_pin, bit_value);
  }
}

byte getData() {
  byte DATA_BITS_COUNT = 8;
  byte dataToReturn
  for (byte data_bit_number = 0; data_bit_number < DATA_BITS_COUNT; data_bit_number++) {
    int bit_pin = IO_PINS[data_bit_number];
    bool bit_value = digitalRead;
    digitalWrite(bit_pin, bit_value);
  }
  return dataToReturn
}

void disableAllControlPins() {
  disableChip();
  disableWrite();
  disableOutput();
  delayMicroseconds(CHIP_MAX_HOLD_TIME_MICROSECONDS);
  setData(0);
}

void pulseWriteControlSignal() {
  enableWrite();
  enableChip();
  const int MAX_WRITE_CYCLE_TIME_MICROSECONDS = 1;
  delayMicroseconds(MAX_WRITE_CYCLE_TIME_MICROSECONDS);
  disableAllControlPins();
}

bool writeToEEPROM(short address, byte data) {
  disableAllControlPins();
  if (!setAddress(address)) {
    return false;
  }
  setData(data);
  pulseWriteControlSignal();
  return true;
}

byte readFromEEPROM(short address) {
  disableAllControlPins()
  if (!setAddress(address)) {
    return 0;
  }
}

void setupPinModesForEEPROMWriting() {
  pinArrayMode(ADDRESS_PINS, OUTPUT);
  pinArrayMode(IO_PINS, OUTPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, OUTPUT);
}

void setupPinModesForEEPROMReading() {
  pinArrayMode(ADDRESS_PINS, OUTPUT);
  pinArrayMode(IO_PINS, INPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, OUTPUT);
}
