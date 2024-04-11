#pragma once
#include"..\base\instruction.h"

//int×óÎ»ÒÆ
class ISHL :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//intËãÊõÓÒÒÆ
class ISHR :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//intÂß¼­ÓÒÒÆ
class IUSHR :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//long×óÎ»ÒÆ
class LSHL :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//longËãÊõÓÒÒÆ
class LSHR :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//longÂß¼­ÓÒÒÆ
class LUSHR :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

