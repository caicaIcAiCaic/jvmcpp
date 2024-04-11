#pragma once
#include"../base/instruction.h"

//instanceofָ����Ҫ����������
//1��uint16������ͨ���������������ʱ���������ҵ�һ�����������
//2���������ã��Ӳ�����ջ�е���
class INSTANCE_OF :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//checkcastָ���instanceofָ�������������instanceofָ���ı������ջ
//checkcastָ��ı������ջ������ж�ʧ����ֱ���׳��쳣��
class CHECK_CAST :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

