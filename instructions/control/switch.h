#pragma once
#include"..\base\instruction.h"

//Java语言中的switch-case指令有两种实现方式：
//	1.case值可以被编码成一个索引表，用tableswitch指令
//	2.否则使用lookupswitch指令
//	参考《Java虚拟机规范》3.10
class TABLE_SWITCH :public Instruction
{
private:
	int defaultOffset = 0;
	int low = 0;
	int high = 0;
	vector<int> jumpOffsets;	//释放
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


