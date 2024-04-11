#pragma once
#include"..\base\instruction.h"

class NOP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

