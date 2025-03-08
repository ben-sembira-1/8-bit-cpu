#include <Arduino.h>
#include <AUnit.h>

const int ADDRESS_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// const int IO_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int IO_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};
const int WRITE_ENABLE_PIN = 11;
const int OUTPUT_ENABLE_PIN = 12;
const int CHIP_ENABLE_PIN = 13;

const int CHIP_MAX_HOLD_TIME_MILLISCONDS = 1;

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

void pinModeAndLog(uint8_t pin, uint8_t mode){
    pinMode(pin, mode);
    Serial.println("Set pin " + String(pin) + " mode to: " + String(mode));
}

void pinArrayMode(int pins[], int pinsLength, int mode) {
  Serial.println("Setting " + String(pinsLength) + " pins... ");

  for (int i = 0; i < pinsLength; i++) {
    pinModeAndLog(pins[i], mode);
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

byte readData() {
  byte DATA_BITS_COUNT = 8;
  byte data = 0;
  for (byte bit_number = 0; bit_number < DATA_BITS_COUNT; bit_number++) {
    bool bit_value = bitRead(data, bit_number);
    int bit_pin = IO_PINS[bit_number];
    data &= digitalRead(bit_pin);
    data = data << 1;
    Serial.println("Reading data[" + String(bit_number) + "/8]: " + String(data));
  }
}

void disableAllControlPins() {
  disableChip();
  disableWrite();
  disableOutput();
  delay(CHIP_MAX_HOLD_TIME_MILLISCONDS);
  setData(0);
}

void pulseWriteControlSignal() {
  enableWrite();
  enableChip();
  const int MAX_WRITE_CYCLE_TIME_MILLISECONDS = 1;
  delay(MAX_WRITE_CYCLE_TIME_MILLISECONDS);
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

struct EEPROMReading readFromEEPROM(short address) {
  EEPROMReading result;
  result.data = 0;
  result.success = false;

  disableAllControlPins();
  enableChip();
  enableOutput();
  if (!setAddress(address)) {
    return result;
  }
  const int CHIP_OUTPUT_PROPEGATION_DELAY_MILLISECONDS = 1;
  delay(CHIP_OUTPUT_PROPEGATION_DELAY_MILLISECONDS);
  result.data = readData();
  result.success = true;
  disableAllControlPins();
  return result;
}

void setupPinModesForEEPROMWriting() {
  pinArrayMode(ADDRESS_PINS, intArrayLength(ADDRESS_PINS), OUTPUT);
  pinArrayMode(IO_PINS, intArrayLength(IO_PINS), OUTPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, intArrayLength(ENABLE_PINS), OUTPUT);
}

void setupPinModesForEEPROMReading() {
  pinArrayMode(ADDRESS_PINS, intArrayLength(ADDRESS_PINS), OUTPUT);
  pinArrayMode(IO_PINS, intArrayLength(IO_PINS), INPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, intArrayLength(ENABLE_PINS), OUTPUT);
}
