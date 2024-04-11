#pragma once
#include"..\base\instruction.h"

//if<cond>ָ��Ѳ�����ջ����int����������Ȼ���0�Ƚϣ�������������ת
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
