#pragma once
#include"..\base\instruction.h"

//equals
class IF_ICMPEQ :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//not equals
class IF_ICMPNE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//if_icmplt succeeds if and only if value1 < value2
class IF_ICMPLT :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//if_icmple succeeds if and only if value1 <= value2
class IF_ICMPLE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//if_icmpgt succeeds if and only if value1 > value2
class IF_ICMPGT :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//if_icmpge succeeds if and only if value1 >= value2
class IF_ICMPGE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//弹出栈顶的两个引用
class IF_ACMPEQ :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class IF_ACMPNE :public Instruction
{
private:
	int offset;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
