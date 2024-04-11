#pragma once
#include"..\base\instruction.h"

//Java�����е�switch-caseָ��������ʵ�ַ�ʽ��
//	1.caseֵ���Ա������һ����������tableswitchָ��
//	2.����ʹ��lookupswitchָ��
//	�ο���Java������淶��3.10
class TABLE_SWITCH :public Instruction
{
private:
	int defaultOffset = 0;
	int low = 0;
	int high = 0;
	vector<int> jumpOffsets;	//�ͷ�
	int jumpOffsetsCount = 0;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class LOOKUP_SWITCH :public Instruction
{
private:
	int defaultOffset = 0;
	int npairs = 0;
	vector<int> matchOffsets;
	//int matchOffsetsCount = 0;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


