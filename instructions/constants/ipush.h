#pragma once

#include"..\base\instruction.h"

class BIPUSH :public Instruction
{
private:
	char val;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class SIPUSH :public Instruction
{
private:
	short val;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};



