#pragma once
#include"..\..\rtda\frame.h"

//重新设置相应的PC值
class BaseLogic {
public:
	static void branch(Frame* frame, int offset);
	//将常量放入栈顶
	static void _ldc(Frame* frame, unsigned int index);
	//在定位到需要调用的方法之后，Java虚拟机要给这个方法创建一个新的栈帧并把它推入Java虚拟机栈顶
	static void invokeMethod(Frame* invokerFrame, Method* method);
	//初始化类：执行<clinit>方法
	static void initClass(Thread* t, Class* c);

private:
	static void scheduleClinit(Thread* t, Class* c);
	static void initSuperClass(Thread* t, Class* c);
};


