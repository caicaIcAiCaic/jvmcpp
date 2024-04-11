#pragma once
#include"../base/instruction.h"

//putField指令给实例变量赋值，它需要三个操作数
//1、运行时常量池索引
//2、变量值
//3、对象的引用：从操作数栈中弹出
class PUT_FIELD :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//getField指令是获取对象的实例变量值，然后推入操作数栈；需要两个操作数
//1、uint16的运行时常量池索引
//2、对象引用
class GET_FIELD :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
