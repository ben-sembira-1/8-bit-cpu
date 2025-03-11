#include "utils.h"

void redPrintln(String s)
{
	Serial.println("\033[31m" + s + "\033[0m");
}

void greenPrintln(String s)
{
	Serial.println("\033[32m" + s + "\033[0m");
}

void hardwareBreakpoint()
{
	digitalWrite(HW_BREAKPOINT_PIN, HIGH);
	digitalWrite(HW_BREAKPOINT_PIN, LOW);
	digitalWrite(HW_BREAKPOINT_PIN, HIGH);
}

void setupHWBreakpoint()
{
	digitalWrite(HW_BREAKPOINT_PIN, HIGH);
	pinMode(HW_BREAKPOINT_PIN, OUTPUT);
}
