#pragma once
#include"../base/instruction.h"

//putFieldָ���ʵ��������ֵ������Ҫ����������
//1������ʱ����������
//2������ֵ
//3����������ã��Ӳ�����ջ�е���
class PUT_FIELD :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//getFieldָ���ǻ�ȡ�����ʵ������ֵ��Ȼ�����������ջ����Ҫ����������
//1��uint16������ʱ����������
//2����������
class GET_FIELD :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
