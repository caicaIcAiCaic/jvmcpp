#pragma once
#include"../base/instruction.h"

//����ջ������������
class SWAP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

