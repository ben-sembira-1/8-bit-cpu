#include <AUnit.h>
#include "utils.h"
#include "ControlLogic.h"
#include "28c16EEPROM.h"

#define OPTION_OUTPUT_EEPROM (0)
#define OPTION_CONTROL_EEPROM (1)

enum class Program
{
  OUTPUT_UNIT,
  CONTROL_LOGIC,
};

// -------------------------
// For choosing the program:
const Program PROGRAM = Program::OUTPUT_UNIT;
// -------------------------


void setup()
{
  setupHWBreakpoint();
  Serial.begin(9600);
  Serial.println("\n\n=== EEPROM FLASHER ===");
  switch (PROGRAM)
  {
  case Program::OUTPUT_UNIT:
    Serial.println(">>> Flashing Output Unit <<<\n");
    setupPinModesForEEPROMWriting();
    flashAll8BitNumbersDigits();
    validateOutputEeprom();
    break;

  case Program::CONTROL_LOGIC:
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
