#pragma once
#include"../base/instruction.h"

//根据Java虚拟机规范，athrow指令从操作数栈中弹出objectref，objectref必须是
//引用数据类型。而且它是Throwable或者Throwable子类的实例。之后在方法的异常处理表
//中查找相应的handler

class ATHROW :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	//寻找并跳转到异常处理代码
	bool findAndGotoExceptionHandler(Thread* t, Object* ex);
	//如果遍历完Java虚拟机栈还是找不到异常处理代码，则打印Java虚拟机栈信息
	void handleUncaughtException(Thread* t, Object* ex);
};


