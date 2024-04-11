#pragma once
#include"..\base\instruction.h"

//Branch always (wide index)
class GOTO_W :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


