#include"Class0.h"
#include"../../../rtda/heap/string_pool.h"

void Class0::getPrimitiveClass(Frame* frame)
{
	Object* nameObj = frame->localVariablesTable.getRef(0);
	string name = StringPool::cppString(nameObj);	//�Ӿֲ�������õ�����

	//���ڻ������͵����Ѿ����ص��������У�ֱ�ӵ�������ؼ��ؼ���
	ClassLoader* loader = frame->method->getClass()->getClassLoader();
	Object* c = loader->loadClass(name)->getJClass();

	frame->operandStack.pushRef(c);
}

void Class0::getName0(Frame* frame)
{
	//�õ�this����
	Object* t = frame->localVariablesTable.getRef(0);
	Class* c = (Class*)t->getExtra();

	//��java/lang/Object����ʽ���java.lang.Object����ʽ
	string name = c->JavaName();
	Object* nameObj = StringPool::JString(c->getClassLoader(), name);
	
	frame->operandStack.pushRef(nameObj);
}

void Class0::desiredAssertionStatus0(Frame* frame)
{
	//��ʵ�ֶ��ԣ�ֱ�Ӱ�false���������ջ��
	frame->operandStack.pushInt(0);
}
