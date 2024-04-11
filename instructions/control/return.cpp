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
	Object* retVal = currentFrame->operandStack.popRef();	//�򵽵�ǰջ֡�еķ���ֵ

	t->popFrame();		//���ٵ�ǰջ֡

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushRef(retVal);	//������ֵѹ����÷����Ĳ�����ջ
}


void DRETURN::fetchOperands(BytecodeReader* reader)
{

}
void DRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	double retVal = currentFrame->operandStack.popDouble();	//�򵽵�ǰջ֡�еķ���ֵ

	t->popFrame();		//���ٵ�ǰջ֡

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushDouble(retVal);	//������ֵѹ����÷����Ĳ�����ջ
}

void FRETURN::fetchOperands(BytecodeReader* reader)
{

}
void FRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	float retVal = currentFrame->operandStack.popFloat();	//�򵽵�ǰջ֡�еķ���ֵ

	t->popFrame();		//���ٵ�ǰջ֡

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushFloat(retVal);	//������ֵѹ����÷����Ĳ�����ջ
}


void IRETURN::fetchOperands(BytecodeReader* reader)
{

}
void IRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	int retVal = currentFrame->operandStack.popInt();	//�򵽵�ǰջ֡�еķ���ֵ

	t->popFrame();		//���ٵ�ǰջ֡

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushInt(retVal);	//������ֵѹ����÷����Ĳ�����ջ
}


void LRETURN::fetchOperands(BytecodeReader* reader)
{

}
void LRETURN::execute(Frame* frame)
{
	Thread* t = frame->thread;
	Frame* currentFrame = t->CurrentFrame();
	long long retVal = currentFrame->operandStack.popLong();	//�򵽵�ǰջ֡�еķ���ֵ

	t->popFrame();		//���ٵ�ǰջ֡

	Frame* invokerFrame = t->CurrentFrame();
	invokerFrame->operandStack.pushLong(retVal);	//������ֵѹ����÷����Ĳ�����ջ
}
