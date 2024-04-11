#include"Object0.h"
#include"../../../rtda/heap/class_loader.h"

void Object0::getClass(Frame* frame)
{
	Object* t = frame->localVariablesTable.getRef(0);
	Object* c = t->getClass()->getJClass();
	frame->operandStack.pushRef(c);
}

void Object0::hashCode(Frame* frame)
{
	void* t = frame->localVariablesTable.getRef(0);
    long long temp = (long long)t;
	frame->operandStack.pushInt(temp ^ (temp >> 32));  //������Java HashMap��hash�ļ��㷽ʽ�����Գ�����ø��������Լ��ٹ�ϣ��ͻ
}

void Object0::clone(Frame* frame)
{
	Object* t = frame->localVariablesTable.getRef(0);

	Class* cloneable = t->getClass()->getClassLoader()->loadClass("java/lang/Cloneable");
	if (!t->getClass()->isImplements(cloneable))
	{
		cout << "java.lang.CloneNotSupportedException" << endl;
		exit(0);
	}

	frame->operandStack.pushRef(t->Clone());
}