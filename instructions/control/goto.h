#pragma once
#include"..\base\instruction.h"


class GOTO :public Instruction
{
private:
	int offset;	//´æ·ÅÌø×ªÆ«ÒÆÁ¿
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};