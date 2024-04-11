#include"return.h"
#include"..\..\rtda\thread.h"

void RETURN::fetchOperands(BytecodeReader* reader)
{

}
void RETURN::execute(Frame* frame)
{
	frame->thread->popFrame();
}

void ARETURN::fetchOperands(BytecodeReader* reader)
{

}
void ARETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	Object* retVal = currentFrame->operandStack.popRef();	//则到当前栈帧中的返回值

	t->popFrame();		//销毁当前栈帧

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushRef(retVal);	//将返回值压入调用方法的操作数栈
}


void DRETURN::fetchOperands(BytecodeReader* reader)
{

}
void DRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	double retVal = currentFrame->operandStack.popDouble();	//则到当前栈帧中的返回值

	t->popFrame();		//销毁当前栈帧

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushDouble(retVal);	//将返回值压入调用方法的操作数栈
}

void FRETURN::fetchOperands(BytecodeReader* reader)
{

}
void FRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	float retVal = currentFrame->operandStack.popFloat();	//则到当前栈帧中的返回值

	t->popFrame();		//销毁当前栈帧

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushFloat(retVal);	//将返回值压入调用方法的操作数栈
}


void IRETURN::fetchOperands(BytecodeReader* reader)
{

}
void IRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	int retVal = currentFrame->operandStack.popInt();	//则到当前栈帧中的返回值

	t->popFrame();		//销毁当前栈帧

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushInt(retVal);	//将返回值压入调用方法的操作数栈
}


void LRETURN::fetchOperands(BytecodeReader* reader)
{

}
void LRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	long long retVal = currentFrame->operandStack.popLong();	//则到当前栈帧中的返回值

	t->popFrame();		//销毁当前栈帧

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushLong(retVal);	//将返回值压入调用方法的操作数栈
}
