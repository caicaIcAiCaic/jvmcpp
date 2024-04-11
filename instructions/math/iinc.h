#pragma once
#include"..\base\instruction.h"

//Increment local variable by constant
//wideָ���iinc������չʱҪʹ�ö�̬
class IINC :public Instruction
{
private:
	unsigned int index = 0;
	int _const = 0;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
	void setConst(int _c);
};

