#include "Throwable0.h"
#include"../../../rtda/thread.h"
#include"../../../rtda/heap/class.h"

void Throwable0::fillInStackTrace(Frame* frame)
{
	Object* tObj = frame->localVariablesTable.getRef(0);
	frame->operandStack.pushRef(tObj);

	StackTraceElement* stes = createStackTraceElements(tObj, frame->thread);

	//至此完成了Java虚拟机栈信息的填写
	tObj->setExtra(stes);
}

StackTraceElement* Throwable0::createStackTraceElements(Object* tObj, Thread* t)
{
	//栈顶的两帧是fillInStackTrace(int)和fillInStackTrace()
	//另外还需要跳过下面的正在执行异常类构造函数的几个帧
	//具体多少帧要看类的继承层次
	int skip = distanceToObject(tObj->getClass()) + 2;

	vector<Frame*> frames = t->getFrames();
	int endPos = frames.size() - skip;

	//数组的第一个元素表示有多少元素（数组的长度）
	StackTraceElement* stes = new StackTraceElement[endPos + 1];
	stes[0].lineNumber = endPos + 1;

	for (int i = 0; i < endPos; i++)
	{
		Method* m = frames[endPos - 1 - i]->method;
		Class* c = m->getClass();

		stes[i + 1] = { c->getSourceFile() ,c->JavaName() ,m->getName() ,
		   m->getLineNumber(frames[i]->getNextPC() - 1) };
	}

	return stes;
}

int Throwable0::distanceToObject(Class* c)
{
	int distance = 0;
	for (c = c->getSuperClass(); c != nullptr; c = c->getSuperClass()) distance++;
	return distance;
}


