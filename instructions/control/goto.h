#pragma once
#include"..\base\instruction.h"


class GOTO :public Instruction
{
private:
	int offset;	//�����תƫ����
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};