#pragma once
#include"../base/instruction.h"

//invoke_virtualָ��������е��鷽��
class INVOKE_VIRTUAL :public Instruction
{
	//hack!
private:
	unsigned int index;	//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	//hack!
	void _println(Frame* frame, string descriptor);
};

