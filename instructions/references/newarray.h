#pragma once
#include"../base/instruction.h"

class ClassLoader;

//newarray用于创建基本数据类型数组：bool[] byte[] char[] short[] int[] long[] float[] double[]
//第一个操作数占1字节，跟在操作码后面，表示创建什么类型的数组
//第二个操作数占count，从操作数栈中弹出
class NEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//1字节
public:
	void fetchOperands(BytecodeReader* reader);	
	void execute(Frame* frame);		
private:
	Class* getPrimitiveArrayClass(ClassLoader* loader, unsigned int atype);
};


//anewarray指令用于创建引用类型数组
//第一个操作数指向运行时常量池的一个类符号引用
//第二个操作数是数组长度，从操作数栈中弹出
class ANEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//2字节
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	
};


//arraylength指令用于获取数组长度
class ARRAY_LENGTH :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
