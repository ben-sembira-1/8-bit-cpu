#include <AUnit.h>

#define VERBOSE (false)
#define DEBUG (false)
#define TEST (false)

#define OPTION_OUTPUT_EEPROM (0)
#define OPTION_CONTROL_EEPROM (1)

enum Program
{
  OUTPUT_UNIT,
  CONTROL_LOGIC,
};

// -------------------------
// For choosing the program:
const Program PROGRAM = OUTPUT_UNIT;
// -------------------------

struct EEPROMReading
{
  byte data;
  bool success;
};

void redPrintln(String s)
{
  Serial.println("\033[31m" + s + "\033[0m");
}

void greenPrintln(String s)
{
  Serial.println("\033[32m" + s + "\033[0m");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n=== EEPROM FLASHER ===");
  switch (PROGRAM)
  {
  case OUTPUT_UNIT:
    Serial.println(">>> Flashing Output Unit <<<\n");
    setupPinModesForEEPROMWriting();
    flashAll8BitNumbersDigits();
    validateOutputEeprom();
    break;

  case CONTROL_LOGIC:
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
