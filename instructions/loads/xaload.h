#pragma once
#include"..\base\instruction.h"

//<t>aload系列指令按索引取数组元素值，然后推入操作数栈
class AALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class BALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class CALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class DALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class FALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class IALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class LALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class SALOAD :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

