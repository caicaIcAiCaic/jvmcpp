#pragma once
#include"../base/instruction.h"

//new指令的操作数时一个2字节的索引，通过这个索引，可以从当前类的运行时常量池中找到一个类符号引用
//解析这个类符号引用，解析这个类符号引用，拿到类数据，然后创建对象，并把对象引用推入栈顶
class NEW :public Instruction
{
private:
	unsigned int index;
public:
	void fetchOperands(BytecodeReader* reader);	//从字节码中提取操作数
	void execute(Frame* frame);		//执行指令逻辑

};