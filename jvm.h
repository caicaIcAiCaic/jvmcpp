#pragma once
#include "cmd.h"
#include "rtda/heap/class_loader.h"
#include "interpreter.h"

class JVM
{
private:
	cmd* myCmd;
	ClassPath* cp;
	ClassLoader* loader;
	Thread* mainThread;
	Interpreter* interpreter;
public:
	JVM(cmd* c);
	~JVM();
	void start();
private:
	//先加载sun.misc.VM类，并初始化
	void initJVM();
	//加载主类，执行main方法
	void execMain();

	//将传递给main函数的args参数数组转换成Java字符串数组，并将其放入局部变量表
	Object* createArgsArray();
};

