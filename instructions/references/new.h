#pragma once
#include"../base/instruction.h"

//newָ��Ĳ�����ʱһ��2�ֽڵ�������ͨ��������������Դӵ�ǰ�������ʱ���������ҵ�һ�����������
//���������������ã����������������ã��õ������ݣ�Ȼ�󴴽����󣬲��Ѷ�����������ջ��
class NEW :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);	//���ֽ�������ȡ������
	void execute(Frame* frame);		//ִ��ָ���߼�

};