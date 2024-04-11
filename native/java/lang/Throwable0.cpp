#include "Throwable0.h"
#include"../../../rtda/thread.h"
#include"../../../rtda/heap/class.h"

void Throwable0::fillInStackTrace(Frame* frame)
{
	Object* tObj = frame->localVariablesTable.getRef(0);
	frame->operandStack.pushRef(tObj);

	StackTraceElement* stes = createStackTraceElements(tObj, frame->thread);

	//���������Java�����ջ��Ϣ����д
	tObj->setExtra(stes);
}

StackTraceElement* Throwable0::createStackTraceElements(Object* tObj, Thread* t)
{
	//ջ������֡��fillInStackTrace(int)��fillInStackTrace()
	//���⻹��Ҫ�������������ִ���쳣�๹�캯���ļ���֡
	//�������֡Ҫ����ļ̳в��
	int skip = distanceToObject(tObj->getClass()) + 2;

	vector<Frame*> frames = t->getFrames();
	int endPos = frames.size() - skip;

	//����ĵ�һ��Ԫ�ر�ʾ�ж���Ԫ�أ�����ĳ��ȣ�
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


