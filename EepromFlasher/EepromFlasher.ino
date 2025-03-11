#include <AUnit.h>

#define VERBOSE (false)
#define DEBUG (false)
#define TEST (false)

#define OPTION_OUTPUT_EEPROM (0)
#define OPTION_CONTROL_EEPROM (1)

const int PROGRAM = OPTION_OUTPUT_EEPROM;

struct EEPROMReading
{
  byte data;
  bool success;
};

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n=== EEPROM FLASHER ===");
  switch (PROGRAM)
  {
  case OPTION_OUTPUT_EEPROM:
    Serial.println(">>> Flashing Output Unit <<<\n");
    setupPinModesForEEPROMWriting();
    flashAll8BitNumbersDigits();
    validateOutputEeprom();
    break;

  case OPTION_CONTROL_EEPROM:
    Serial.println(">>> Flashing Control Logic <<<\n");
    redPrintln("NOT IMPLEMENTED");
    break;

  default:
    break;
  }
}

void loop()
{
  if (TEST)
  {
    aunit::TestRunner::run();
  }
}
