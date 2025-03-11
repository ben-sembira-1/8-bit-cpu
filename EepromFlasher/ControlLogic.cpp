#include "ControlLogic.h"

byte buildControlSignal(LoadControl load, OutputControl out, HaltControl halt, PCControl pc)
{
	return (static_cast<byte>(load)) |
		   (static_cast<byte>(out) << 3) |
		   (static_cast<byte>(halt) << 6) |
		   (static_cast<byte>(pc) << 7);
}

const byte FETCH_COMMAND[] = {
	buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::PROGRAM_COUNTER, HaltControl::NOP, PCControl::NOP),
	buildControlSignal(LoadControl::INSTRUCTION_REGISTER, OutputControl::RAM, HaltControl::NOP, PCControl::INCREMENT),
};

void flashAllControlSignals()
{
	redPrintln("NOT IMPLEMENTED");
}

void validateControlLogicEeprom()
{
	redPrintln("NOT IMPLEMENTED");
}
