#include"instruction.h"

const char* Instruction::toString()
{
	return typeid(*this).name();
}