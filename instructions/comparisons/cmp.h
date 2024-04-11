#pragma once
#include"..\base\instruction.h"

//���ȽϽṹ���뵽������ջ��
class LCMP :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//�������п�����NANֵ(Not a number)
//���Ƚϵ�����float��������һ��NANʱ���ȽϽ��Ϊ-1
class FCMPL :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
//���Ƚϵ�����float��������һ��NANʱ���ȽϽ��Ϊ1
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
//���Ƚϵ�����float��������һ��NANʱ���ȽϽ��Ϊ1
class DCMPG :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

