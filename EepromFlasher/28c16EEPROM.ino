#include <Arduino.h>
#include <AUnit.h>

const int ADDRESS_PINS[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42};
// const int IO_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int IO_PINS[] = {39, 41, 43, 45, 47, 49, 51, 53};
const int WRITE_ENABLE_PIN = 48;
const int OUTPUT_ENABLE_PIN = 50;
const int CHIP_ENABLE_PIN = 52;

const int HW_BREAKPOINT_PIN = 31;

const int CHIP_MAX_HOLD_TIME_MILLISCONDS = 1;

#define intArrayLength(arr) int(sizeof(arr) / sizeof(int))

void hardwareBreakpoint() {
  digitalWrite(HW_BREAKPOINT_PIN, HIGH);
  digitalWrite(HW_BREAKPOINT_PIN, LOW);
  digitalWrite(HW_BREAKPOINT_PIN, HIGH);
}

void pinModeAndLog(uint8_t pin, uint8_t mode){
    pinMode(pin, mode);
    if (DEBUG) {
      Serial.println("pin mode: " + String(pin) + " -> " + String(mode));
    }
}

void digitalWriteAndLog(uint8_t pin, uint8_t value){
    digitalWrite(pin, value);
    if (DEBUG) {
      Serial.println("[WRITE] pin: " + String(pin) + " <- " + String(value));
    }
}

int digitalReadAndLog(uint8_t pin){
    int value = digitalRead(pin);
    if (DEBUG) {
          Serial.println("[READ] pin: " + String(pin) + " -> " + String(value));
    }
    return value;
}

void pinArrayMode(int pins[], int pinsLength, int mode) {
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
  if (VERBOSE) {
    Serial.println(">>> Setting address: " + String(address) + " <<<");
  }
  for (byte address_bit_number = 0; address_bit_number < ADDRESS_BITS; address_bit_number++) {
    bool bit_value = bitRead(address, address_bit_number);
    int bit_pin = ADDRESS_PINS[address_bit_number];
    digitalWriteAndLog(bit_pin, bit_value);
  }
  return true;
}

void setDataLogging(byte data, bool shouldLog) {
  byte DATA_BITS_COUNT = 8;
  for (byte data_bit_number = 0; data_bit_number < DATA_BITS_COUNT; data_bit_number++) {
    bool value = bitRead(data, data_bit_number);
    int pin = IO_PINS[data_bit_number];
    if (shouldLog) {
      digitalWriteAndLog(pin, value);
    }
    else {
      digitalWrite(pin, value);
    }
  }
}

void setData(byte data) {
  if (VERBOSE) {
    Serial.println(">>> Setting data: " + String(data) + " <<<");
  }
  setDataLogging(data, true);
}

byte readData() {
  byte DATA_BITS_COUNT = 8;
  byte data = 0;
  for (byte bit_number = 0; bit_number < DATA_BITS_COUNT; bit_number++) {
    bool bit_value = bitRead(data, bit_number);
    int bit_pin = IO_PINS[bit_number];
    bitWrite(data, bit_number, digitalReadAndLog(bit_pin));
  }
  return data;
}

void disableAllControlPins() {
  disableChip();
  disableWrite();
  disableOutput();
  delay(CHIP_MAX_HOLD_TIME_MILLISCONDS);
  setDataLogging(0, false);
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

  enableOutput();
  if (!setAddress(address)) {
    return result;
  }
  enableChip();
  const int CHIP_OUTPUT_PROPEGATION_DELAY_MILLISECONDS = 1;
  delay(CHIP_OUTPUT_PROPEGATION_DELAY_MILLISECONDS);
  result.data = readData();
  result.success = true;
  disableAllControlPins();
  return result;
}

void generalSetup() {
  disableChip();
  disableOutput();
  disableWrite();
}

void setupPinModesForEEPROMWriting() {
  generalSetup();
  pinArrayMode(ADDRESS_PINS, intArrayLength(ADDRESS_PINS), OUTPUT);
  pinArrayMode(IO_PINS, intArrayLength(IO_PINS), OUTPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, intArrayLength(ENABLE_PINS), OUTPUT);
  pinMode(HW_BREAKPOINT_PIN, OUTPUT);
}

void setupPinModesForEEPROMReading() {
  generalSetup();
  pinArrayMode(ADDRESS_PINS, intArrayLength(ADDRESS_PINS), OUTPUT);
  pinArrayMode(IO_PINS, intArrayLength(IO_PINS), INPUT);
  const int ENABLE_PINS[3] = {CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN};
  pinArrayMode(ENABLE_PINS, intArrayLength(ENABLE_PINS), OUTPUT);
  pinMode(HW_BREAKPOINT_PIN, OUTPUT);
}
