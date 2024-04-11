#pragma once
#include"../base/instruction.h"

//invoke_special指令用于调用实例构造器<init>方法、私有方法和父类中的方法
//私有方法和构造函数不需要动态分派，所以invoke_special可以加快方法调用的速度
//其次，super关键字调用的方法不能使用使用invoke_virtual指令
class INVOKE_SPECIAL :public Instruction
{
	//hack!
private:
	unsigned int index;	//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

