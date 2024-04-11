#pragma once
#include"..\base\instruction.h"

//Extend local variable index by additional bytes
class WIDE :public Instruction
{
private:
	Instruction* inst = NULL;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	~WIDE();
};