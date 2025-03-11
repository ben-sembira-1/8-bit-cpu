#include "ControlLogic.h"

byte buildControlSignal(LoadControl load, OutputControl out, HaltControl halt, PCControl pc)
{
	return (static_cast<byte>(load)) |
		   (static_cast<byte>(out) << 3) |
		   (static_cast<byte>(pc) << 6) |
		   (static_cast<byte>(halt) << 7);
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

void flashCommand(byte opcode, const byte *signals, int length, int offset)
{
	for (int i = 0; i < length; i++)
	{
		writeToEEPROM(((i + offset) << OPCODE_LENGTH_BITS) + opcode, signals[i]);
	}
}

void flashAllControlSignals()
{
	setupPinModesForEEPROMWriting();

	flashCommand(0, Commands::FETCH, MAX_FETCH_COMMAND_LENGTH, 0);
	const int opcodesCount = int(sizeof(Commands::ALL_COMMANDS) / sizeof(byte *));
	for (int opcode = 0; opcode < opcodesCount; opcode++)
	{
		flashCommand(opcode, Commands::ALL_COMMANDS[opcode], MAX_AUXILARY_COMMAND_LENGTH, MAX_FETCH_COMMAND_LENGTH);
		Serial.println("Flashed opcode: " + String(opcode));
	}
}

bool fetchFlashedCorrectly()
{
	Serial.println("* Validating FETCH");
	return readFromEEPROM(0x00).data == 0b00011010 &&
		   readFromEEPROM(0x10).data == 0b01010001;
}

bool outputAFlashedCorrectly()
{
	Serial.println("* Validating OUTPUT_A");
	return readFromEEPROM(0x20).data == 0b00111111 &&
		   readFromEEPROM(0x30).data == 0b00000000;
}

bool ramStoreBFlashedCorrectly()
{
	Serial.println("* Validating RAM_STORE_B");
	return readFromEEPROM(0x25).data == 0b00001010 &&
		   readFromEEPROM(0x35).data == 0b00100011 &&
		   readFromEEPROM(0x45).data == 0b00000000;
}

bool haltFlashedCorrectly()
{
	Serial.println("* Validating HALT");
	return readFromEEPROM(0x29).data == 0b10000000 &&
		   readFromEEPROM(0x39).data == 0b00000000;
}

void validateControlLogicEeprom()
{
	setupPinModesForEEPROMReading();
	if (!(fetchFlashedCorrectly() &&
		  outputAFlashedCorrectly() &&
		  ramStoreBFlashedCorrectly() &&
		  haltFlashedCorrectly()))
	{
		redPrintln("Error: signal did not flash correctly.");
		Serial.println();
		return;
	}
	greenPrintln("A sample of signals has been validated successfully.");
	Serial.println("(Keep in mind that not all signals were verified)\n");
}
