#pragma once
#include"../base/instruction.h"

//交换栈顶的两个变量
class SWAP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

