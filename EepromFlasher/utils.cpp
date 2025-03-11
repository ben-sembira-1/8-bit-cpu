#include "utils.h"

void redPrintln(String s)
{
	Serial.println("\033[31m" + s + "\033[0m");
}

void greenPrintln(String s)
{
	Serial.println("\033[32m" + s + "\033[0m");
}