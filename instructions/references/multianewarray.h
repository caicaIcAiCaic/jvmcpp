#pragma once
#include"../base/instruction.h"

//该指令用于创建多维数组
//第一个操作数是2字节索引，通过这个索引可以从运行时常量池中找到一个类符号引用，解析这个引用就可以得到多维数组类、
//第二个操作数表示数组维数
//这两个操作数在字节码中紧跟在指令操作码后面
class MULTI_ANEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//2字节
	unsigned char dimensions;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	vector<int> popAndCheckCounts(OperandStack& stack, int d);	//保证操作数栈d个整数，并且保证它们都大于0
	Object* newMultiDimensionalArray(vector<int>& counts, int d, Class* arrClass);
};