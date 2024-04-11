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
	frame->operandStack.pushInt(temp ^ (temp >> 32));  //类似于Java HashMap中hash的计算方式，可以充分利用高区特征以减少哈希冲突
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