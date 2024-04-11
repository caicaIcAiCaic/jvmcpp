#pragma once
#include"../base/instruction.h"

class POP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class POP2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};




