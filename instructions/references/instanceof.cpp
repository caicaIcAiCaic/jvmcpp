#include"instanceof.h"
#include"../../rtda/heap/class.h"

void INSTANCE_OF::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void INSTANCE_OF::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	Object* ref = stack.popRef();
	
	if (ref == NULL)	//如果对象的引用是null，则直接将0退出操作栈即可
	{
		stack.pushInt(0);
		return;
	}

	//如果对象的引用不是null，则判断对象是否是类的实例，并将判断结果推入操作数栈
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	ClassRefInfo* classRef = (ClassRefInfo*)rtcp->getConstant(index);
	Class* c = classRef->resolvedClass();

	if (ref->IsInstanceOf(c)) stack.pushInt(1);
	else stack.pushInt(0);
}


void CHECK_CAST::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void CHECK_CAST::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	Object* ref = stack.popRef();
	stack.pushRef(ref);		//不改变操作数栈的状态

	if (ref == NULL)	//null可以转换成任何类型
	{
		return;
	}

	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	ClassRefInfo* classRef = (ClassRefInfo*)rtcp->getConstant(index);
	Class* c = classRef->resolvedClass();

	if (!ref->IsInstanceOf(c))
	{
		cout << "java.lang.ClassCastException" << endl;
		exit(0);
	}
}


