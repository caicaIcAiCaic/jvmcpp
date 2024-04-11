#pragma once
#include"../base/instruction.h"

//ldc指令从运行时常量池中加载常量值，并把它推入操作数栈
//ldc和ldc_w用于加载int、float和字符串常量、java.lang.Class实例或MethodType和MethodHandle实例
//ldc2_w用于加载long和double类型
//ldc和ldc_w的区别仅在于操作数的宽度

class LDC :public Instruction
{
private:
	unsigned int index;	//1字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};


class LDC_W :public Instruction
{
private:
	unsigned int index;//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class LDC2_W :public Instruction
{
private:
	unsigned int index;	//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
