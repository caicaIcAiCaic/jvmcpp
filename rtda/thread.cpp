#include"thread.h"

Thread::Thread():pc(0)
{
	
}

int Thread::getPC()
{
	return pc;
}
void Thread::setPC(int p)
{
	pc = p;
}

void Thread::pushFrame(Frame* frame)
{
	JVM_Stack.push_back(frame);
}
void Thread::popFrame() //Ïú»ÙÕ»Ö¡
{
	Frame* temp = JVM_Stack.back();
	JVM_Stack.pop_back();
	delete temp;
}

Frame* Thread::CurrentFrame()
{
	return JVM_Stack.back();
}

bool Thread::isStackEmpty()
{
	return JVM_Stack.empty();
}

void Thread::ClearStack()
{
	JVM_Stack.clear();
}

vector<Frame*>& Thread::getFrames()
{
	return JVM_Stack;
}
