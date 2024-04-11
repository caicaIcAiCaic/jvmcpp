#pragma once
#include"..\base\instruction.h"

//����ջ�������ж��Ƿ���NULL
class IFNULL :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//Branch if reference not null
class IFNONNULL :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

