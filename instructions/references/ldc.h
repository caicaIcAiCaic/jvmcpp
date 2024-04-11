#pragma once
#include"../base/instruction.h"

//ldcָ�������ʱ�������м��س���ֵ�����������������ջ
//ldc��ldc_w���ڼ���int��float���ַ���������java.lang.Classʵ����MethodType��MethodHandleʵ��
//ldc2_w���ڼ���long��double����
//ldc��ldc_w����������ڲ������Ŀ��

class LDC :public Instruction
{
private:
	unsigned int index;	//1�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class LDC_W :public Instruction
{
private:
	unsigned int index;//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class LDC2_W :public Instruction
{
private:
	unsigned int index;	//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
