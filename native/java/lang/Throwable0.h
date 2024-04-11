#pragma once
#include"../../../rtda/frame.h"

struct StackTraceElement
{
	string fileName;
	string className;
	string methodName;
	int lineNumber;
};

class Throwable0
{
public:
	//private native Throwable fillInStackTrace(int dummy)
	static void fillInStackTrace(Frame* frame);
private:
	static StackTraceElement* createStackTraceElements(Object* tObj, Thread* t);
	static int distanceToObject(Class* c);	//计算所需要跳过的帧数
};

