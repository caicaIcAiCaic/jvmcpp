#include"Class0.h"
#include"../../../rtda/heap/string_pool.h"

void Class0::getPrimitiveClass(Frame* frame)
{
	Object* nameObj = frame->localVariablesTable.getRef(0);
	string name = StringPool::cppString(nameObj);	//从局部变量表得到类名

	//由于基本类型的类已经加载到方法区中，直接调用类加载加载即可
	ClassLoader* loader = frame->method->getClass()->getClassLoader();
	Object* c = loader->loadClass(name)->getJClass();

	frame->operandStack.pushRef(c);
}

void Class0::getName0(Frame* frame)
{
	//得到this引用
	Object* t = frame->localVariablesTable.getRef(0);
	Class* c = (Class*)t->getExtra();

	//将java/lang/Object的形式变成java.lang.Object的形式
	string name = c->JavaName();
	Object* nameObj = StringPool::JString(c->getClassLoader(), name);
	
	frame->operandStack.pushRef(nameObj);
}

void Class0::desiredAssertionStatus0(Frame* frame)
{
	//不实现断言，直接把false推入操作数栈顶
	frame->operandStack.pushInt(0);
}
