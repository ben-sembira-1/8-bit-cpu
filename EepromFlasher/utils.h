#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#define VERBOSE (false)
#define DEBUG (false)
#define TEST (false)

#define MAX_BYTE (256)

const int HW_BREAKPOINT_PIN = 31;

void redPrintln(String s);
void greenPrintln(String s);
void hardwareBreakpoint();
void setupHWBreakpoint();

#endif