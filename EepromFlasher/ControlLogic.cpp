#include "ControlLogic.h"

byte buildControlSignal(LoadControl load, OutputControl out, HaltControl halt, PCControl pc)
{
	return (static_cast<byte>(load)) |
		   (static_cast<byte>(out) << 3) |
		   (static_cast<byte>(halt) << 6) |
		   (static_cast<byte>(pc) << 7);
}

namespace Commands
{
	// This implicitly adds NOPs (0x00) at the end of each command
	const byte FETCH[MAX_FETCH_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::PROGRAM_COUNTER, HaltControl::NOP, PCControl::NOP),
		buildControlSignal(LoadControl::INSTRUCTION, OutputControl::RAM, HaltControl::NOP, PCControl::INCREMENT),
	};

	const byte OUTPUT_A[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::OUT_DISPLAY, OutputControl::REGISTER_A, HaltControl::NOP, PCControl::NOP),
	};
	const byte OUTPUT_B[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::OUT_DISPLAY, OutputControl::REGISTER_B, HaltControl::NOP, PCControl::NOP),
	};
	const byte RAM_READ_TO_A[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::INSTRUCTION, HaltControl::NOP, PCControl::NOP),
		buildControlSignal(LoadControl::REGISTER_A, OutputControl::RAM, HaltControl::NOP, PCControl::NOP),
	};
	const byte RAM_READ_TO_B[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::INSTRUCTION, HaltControl::NOP, PCControl::NOP),
		buildControlSignal(LoadControl::REGISTER_B, OutputControl::RAM, HaltControl::NOP, PCControl::NOP),
	};
	const byte RAM_STORE_A[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::INSTRUCTION, HaltControl::NOP, PCControl::NOP),
		buildControlSignal(LoadControl::RAM_DATA, OutputControl::REGISTER_A, HaltControl::NOP, PCControl::NOP),
	};
	const byte RAM_STORE_B[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::RAM_ADDRESS, OutputControl::INSTRUCTION, HaltControl::NOP, PCControl::NOP),
		buildControlSignal(LoadControl::RAM_DATA, OutputControl::REGISTER_B, HaltControl::NOP, PCControl::NOP),
	};
	const byte ADD[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::REGISTER_A, OutputControl::ALU_ADD, HaltControl::NOP, PCControl::NOP),
	};
	const byte SUBTRACT[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::REGISTER_A, OutputControl::ALU_SUBTRACT, HaltControl::NOP, PCControl::NOP),
	};
	const byte JUMP[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::PROGRAM_COUNTER, OutputControl::INSTRUCTION, HaltControl::NOP, PCControl::NOP),
	};
	const byte HALT[MAX_AUXILARY_COMMAND_LENGTH] = {
		buildControlSignal(LoadControl::NOP, OutputControl::NOP, HaltControl::HALT, PCControl::NOP),
	};

	const byte *ALL_COMMANDS[MAX_TOTAL_COMMANDS] = {
		OUTPUT_A,
		OUTPUT_B,
		RAM_READ_TO_A,
		RAM_READ_TO_B,
		RAM_STORE_A,
		RAM_STORE_B,
		ADD,
		SUBTRACT,
		JUMP,
		HALT,
	};
}

// void flashCommand(byte opcode, byte *signals, int length)
// {
// 	if (length > MAX_AUXILARY_COMMAND_LENGTH)
// 	{
// 		redPrintln("Failed to flash command because length is too big.");
// 		return;
// 	}

// 	// TODO: flash all signals
// }

void flashFetch()
{
	
}

void flashAllControlSignals()
{
	redPrintln("NOT IMPLEMENTED");
}

void validateControlLogicEeprom()
{
	redPrintln("NOT IMPLEMENTED");
}
