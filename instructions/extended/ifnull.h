#pragma once
#include"..\base\instruction.h"

//弹出栈顶引用判断是否是NULL
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

