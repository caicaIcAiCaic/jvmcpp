#pragma once
#include"..\base\instruction.h"

//将比较结构推入到操作数栈顶
class LCMP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//浮点数有可能是NAN值(Not a number)
//当比较的两个float变量中有一个NAN时，比较结果为-1
class FCMPL :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//当比较的两个float变量中有一个NAN时，比较结果为1
class FCMPG :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class DCMPL :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//当比较的两个float变量中有一个NAN时，比较结果为1
class DCMPG :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

