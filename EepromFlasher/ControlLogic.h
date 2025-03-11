#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include "utils.h"

#define MAX_AUXILARY_COMMAND_LENGTH (8)
#define MAX_FETCH_COMMAND_LENGTH (2)
#define MAX_TOTAL_COMMANDS (16)

enum class LoadControl
{
	NOP = 0,
	INSTRUCTION = 1,
	RAM_ADDRESS = 2,
	RAM_DATA = 3,
	PROGRAM_COUNTER = 4,
	REGISTER_B = 5,
	REGISTER_A = 6,
	OUT_DISPLAY = 7,
};

enum class OutputControl
{
	NOP = 0,
	INSTRUCTION = 1,
	RAM = 2,
	PROGRAM_COUNTER = 3,
	REGISTER_B = 4,
	ALU_SUBTRACT = 5,
	ALU_ADD = 6,
	REGISTER_A = 7,
};

enum class HaltControl
{
	NOP = 0,
	HALT = 1,
};

enum class PCControl
{
	NOP = 0,
	INCREMENT = 1,
};

#endif