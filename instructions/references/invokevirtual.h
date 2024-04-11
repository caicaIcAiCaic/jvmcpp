#pragma once
#include"../base/instruction.h"

//invoke_virtual指令调用所有的虚方法
class INVOKE_VIRTUAL :public Instruction
{
	//hack!
private:
	unsigned int index;	//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	//hack!
	void _println(Frame* frame, string descriptor);
};

