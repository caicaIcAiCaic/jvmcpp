#pragma once
#include"../base/instruction.h"

//instanceof指令需要两个操作数
//1、uint16索引，通过这个索引从运行时常量池中找到一个类符号引用
//2、对象引用，从操作数栈中弹出
class INSTANCE_OF :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

//checkcast指令和instanceof指令很像，区别在于instanceof指令会改变操作数栈
//checkcast指令不改变操作数栈（如果判断失败则直接抛出异常）
class CHECK_CAST :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

