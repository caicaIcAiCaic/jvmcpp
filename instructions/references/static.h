#pragma once
#include"../base/instruction.h"

//putstatic给某个静态变量赋值，它需要两个操作数
//1、uint16的索引，通过这个索引在当前类的运行时常量池中找到一个字段的符号引用，解析它就会知道给哪个字段赋值
//2、赋给静态变量的值，从操作数栈中弹出
class PUT_STATIC :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);	
};

//getstatic指令只需要一个操作数：uint16常量池索引
class GET_STATIC :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

