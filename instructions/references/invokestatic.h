#pragma once
#include"../base/instruction.h"

//暂不考虑接口的静态方法和默认方法，所以该指令系统并不满足Java虚拟机规范第8版的规定
//invokestatic指令用于调用静态方法
//通过静态分派（解析）来确定调用方法的版本，编译期可知
class INVOKE_STATIC :public Instruction
{
private:
	unsigned int index;	//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

