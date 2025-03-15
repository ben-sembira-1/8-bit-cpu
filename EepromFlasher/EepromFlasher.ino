#include <AUnit.h>
#include "utils.h"
#include "28c16EEPROM.h"
#include "OutputUnit.h"
#include "ControlLogic.h"

#define OPTION_OUTPUT_EEPROM (0)
#define OPTION_CONTROL_EEPROM (1)

enum class Program
{
  OUTPUT_UNIT,
  CONTROL_LOGIC,
};

// -------------------------
// For choosing the program:
const Program PROGRAM = Program::CONTROL_LOGIC;
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
    flashAll8BitNumbersDigits();
    Serial.println("\n>>> Validating Output Unit <<<\n");
    validateOutputEeprom();
    break;
    
    case Program::CONTROL_LOGIC:
    Serial.println(">>> Flashing Control Logic <<<\n");
    flashAllControlSignals();
    Serial.println("\n>>> Validating Control Logic <<<\n");
    validateControlLogicEeprom();
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
