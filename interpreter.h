#pragma once
#include"instructions/base/instruction.h"
#include"rtda/thread.h"
#include"rtda/heap/string_pool.h"

//制作一个简易版的解释器
class Interpreter
{
private:
	bool log;	//标志是否打印指令执行信息
public:
	Interpreter(bool l);
	//interpret方法的参数是MemberInfo指针，即一个方法，从中我们可以得到它的code属性
	void interpret(Thread* thread);
private:
	//该方法会根据传入的操作码返回具体的指令对象
	Instruction* newInstruction(int opcode);
	//将该指令的执行细节打印到控制台
	void logInstruction(Frame* frame, Instruction* inst);
};

