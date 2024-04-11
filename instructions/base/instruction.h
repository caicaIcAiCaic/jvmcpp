#pragma once
#include"..\..\rtda\frame.h"
#include"bytecode_reader.h"

//在JVM里，栈帧中的本地变量表和操作数栈只保存了数据的值，并不记录相应的数据类型
//这样的结果就是每条指令必须知道自己在操作什么类型的数据

//本目录实现一个简易版解释器：其中的每种指令都抽象成接口，解码和执行逻辑卸载具体的指令实现中
class Instruction
{
public:
	virtual void fetchOperands(BytecodeReader* reader) = 0;	//从字节码中提取操作数
	virtual void execute(Frame* frame) = 0;		//执行指令逻辑
	//virtual void setIndex(unsigned int _i) = 0;
	const char* toString();	//返回该指令的名字（即类名字）
};

////没有操作数的指令
//class NoOperandsInstruction
//{
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//
//	}
//};
//
////跳转指令
//class BranchInstruction
//{
//private:
//	int offset;	//存放跳转偏移量
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		offset = int(reader->readInt16());	//从字节码中读取2字节整数
//	}
//};
//
////存储和加载需要根据索引存取局部变量表
//class Index8Instruction
//{
//private:
//	unsigned int index;	//表示局部变量表索引
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		index = unsigned int(reader->readUint8());	//无符号1字节整数
//	}
//};
//
////访问运行时常量池，与访问局部变量表不同，它的操作数是2字节
//class Index16Instruction
//{
//private:
//	unsigned int index;
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		index = unsigned int(reader->readUint16());
//	}
//};

