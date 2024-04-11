#pragma once
#include"frame.h"

class Thread
{
private:
	int pc;	//相当于该线程的程序计数器
	vector<Frame*> JVM_Stack;	//Java虚拟机栈；程序计数器与Java虚拟机栈都是线程私有的
public:
	Thread();

	int getPC();
	void setPC(int p);

	void pushFrame(Frame* frame);
	void popFrame();

	Frame* CurrentFrame();
	bool isStackEmpty();
	void ClearStack();

	vector<Frame*>& getFrames();    //返回所有栈帧（即Java虚拟机栈）
};


