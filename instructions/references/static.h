#pragma once
#include"../base/instruction.h"

//putstatic��ĳ����̬������ֵ������Ҫ����������
//1��uint16��������ͨ����������ڵ�ǰ�������ʱ���������ҵ�һ���ֶεķ������ã��������ͻ�֪�����ĸ��ֶθ�ֵ
//2��������̬������ֵ���Ӳ�����ջ�е���
class PUT_STATIC :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);	
};

//getstaticָ��ֻ��Ҫһ����������uint16����������
class GET_STATIC :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

