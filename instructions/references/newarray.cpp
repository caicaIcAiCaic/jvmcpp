#include"newarray.h"
#include"../../rtda/frame.h"
#include"../../rtda/heap/class_loader.h"

const u1 AT_BOOLEAN = 4;
const u1 AT_CHAR = 5;
const u1 AT_FLOAT = 6;
const u1 AT_DOUBLE = 7;
const u1 AT_BYTE = 8;
const u1 AT_SHORT = 9;
const u1 AT_INT = 10;
const u1 AT_LONG = 11;

void NEW_ARRAY::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint8();
}
void NEW_ARRAY::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int count = stack.popInt();
	
	if (count < 0)
	{
		cout << "java.lang.NegativeArraySizeException" << endl;
		exit(0);
	}

	ClassLoader* cl = frame->method->getClass()->getClassLoader();
	Class* arrClass = getPrimitiveArrayClass(cl, index);
	Object* arr = arrClass->newArray(count);
	stack.pushRef(arr);
}

Class* NEW_ARRAY::getPrimitiveArrayClass(ClassLoader* loader, unsigned int atype)
{
	switch (atype)
	{
	case AT_BOOLEAN:
		return loader->loadClass("[Z");
	case AT_BYTE:
		return loader->loadClass("[B");
	case AT_CHAR:
		return loader->loadClass("[C");
	case AT_SHORT:
		return loader->loadClass("[S");
	case AT_INT:
		return loader->loadClass("[I");
	case AT_LONG:
		return loader->loadClass("[J");
	case AT_FLOAT:
		return loader->loadClass("[F");
	case AT_DOUBLE:
		return loader->loadClass("[D");
	default:
		cout << "Invalid atype" << atype << endl;
		exit(0);
	}
}


void ANEW_ARRAY::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}
void ANEW_ARRAY::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	ClassRefInfo* classRef = (ClassRefInfo*)rtcp->getConstant(index);
	Class* componentClass = classRef->resolvedClass();

	OperandStack& stack = frame->operandStack;
	int count = stack.popInt();

	if (count < 0)
	{
		cout << "java.lang.NegativeArraySizeException" << endl;
		exit(0);
	}

	Class* arrClass = componentClass->getArrayClass();
	Object* arr = arrClass->newArray(count);
	stack.pushRef(arr);
}

void ARRAY_LENGTH::fetchOperands(BytecodeReader* reader)
{

}
void ARRAY_LENGTH::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	Object* arrRef = stack.popRef();

	if (arrRef == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	int arrLen = arrRef->getArrayLength();
	stack.pushInt(arrLen);
}
