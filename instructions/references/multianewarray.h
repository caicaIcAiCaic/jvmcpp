#pragma once
#include"../base/instruction.h"

//��ָ�����ڴ�����ά����
//��һ����������2�ֽ�������ͨ������������Դ�����ʱ���������ҵ�һ����������ã�����������þͿ��Եõ���ά�����ࡢ
//�ڶ�����������ʾ����ά��
//���������������ֽ����н�����ָ����������
class MULTI_ANEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//2�ֽ�
	unsigned char dimensions;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	vector<int> popAndCheckCounts(OperandStack& stack, int d);	//��֤������ջd�����������ұ�֤���Ƕ�����0
	Object* newMultiDimensionalArray(vector<int>& counts, int d, Class* arrClass);
};