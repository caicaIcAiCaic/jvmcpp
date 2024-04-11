#pragma once
#include"..\base\instruction.h"

//if<cond>指令把操作数栈顶的int变量弹出，然后跟0比较，满足条件则跳转
//x==0
class IFEQ :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//x!=0
class IFNE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//x < 0
class IFLT :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//X<=0
class IFLE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//x>0
class IFGT :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//x>=0
class IFGE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
