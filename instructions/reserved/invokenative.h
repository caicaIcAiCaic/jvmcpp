#pragma once
#include"../base/instruction.h"

class INVOKE_NATIVE :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
