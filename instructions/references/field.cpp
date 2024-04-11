#include"field.h"
#include"../../rtda/heap/class.h"

void PUT_FIELD::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void PUT_FIELD::execute(Frame* frame)
{
	Method* currentMethod = frame->method;	//首先得到当前的类与方法
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//得到当前的运行时常量池
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);
	Field* field = fieldRef->resolvedField();	//解析符号引用

	//1、解析后的字段必须是实例字段
	//2、如果是final字段（常量），只能在构造函数中初始化
	if (field->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangError" << endl;
		exit(0);
	}
	if (field->isFinal() && (currentClass != field->getClass() || currentMethod->getName() != "<init>"))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	//根据字段类型从操作数栈中弹出相应的变量值，然后弹出对象引用，通过引用对变量赋值
	string descriptor = field->getDescriptor();
	unsigned int slotId = field->getSlotId();
	OperandStack& stack = frame->operandStack;

	if (descriptor[0] == 'Z' || descriptor[0] == 'B' || descriptor[0] == 'C' || descriptor[0] == 'S' || descriptor[0] == 'I')
	{
		int val = stack.popInt();
		Object* ref = stack.popRef();
		if (ref == nullptr) {
			cout << "java.lang.NullPointerException" << endl;
			exit(0);
		}
		ref->getFields()->setInt(slotId, val);
	}
	else if (descriptor[0] == 'F')
	{
		float val = stack.popFloat();
		Object* ref = stack.popRef();
		if (ref == nullptr) {
			cout << "java.lang.NullPointerException" << endl;
			exit(0);
		}
		ref->getFields()->setFloat(slotId, val);
	}
	else if (descriptor[0] == 'J')
	{
		long long val = stack.popLong();
		Object* ref = stack.popRef();
		if (ref == nullptr) {
			cout << "java.lang.NullPointerException" << endl;
			exit(0);
		}
		ref->getFields()->setLong(slotId, val);
	}
	else if (descriptor[0] == 'D')
	{
		double val = stack.popDouble();
		Object* ref = stack.popRef();
		if (ref == nullptr) {
			cout << "java.lang.NullPointerException" << endl;
			exit(0);
		}
		ref->getFields()->setDouble(slotId, val);
	}
	else if (descriptor[0] == 'L' || descriptor[0] == '[')
	{
		Object* val = stack.popRef();
		Object* ref = stack.popRef();
		if (ref == nullptr) {
			cout << "java.lang.NullPointerException" << endl;
			exit(0);
		}
		ref->getFields()->setRef(slotId, val);
	}
	
}


void GET_FIELD::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void GET_FIELD::execute(Frame* frame)
{
	Method* currentMethod = frame->method;	//首先得到当前的类与方法
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//得到当前的运行时常量池
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);
	Field* field = fieldRef->resolvedField();	//解析符号引用

	//1、解析后的字段必须是实例字段
	if (field->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangError" << endl;
		exit(0);
	}

	//弹出的对象引用如果是null，则抛出异常
	OperandStack& stack = frame->operandStack;
	Object* ref = stack.popRef();
	if (ref == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	string descriptor = field->getDescriptor();
	unsigned int slotId = field->getSlotId();
	Slots* slots = ref->getFields();

	switch (descriptor[0])
	{
	case 'Z':
	case 'B':
	case 'C':
	case 'S':
	case 'I': stack.pushInt(slots->getInt(slotId)); break;
	case 'F':stack.pushFloat(slots->getFloat(slotId)); break;
	case 'J':stack.pushLong(slots->getLong(slotId)); break;
	case 'D':stack.pushDouble(slots->getDouble(slotId)); break;
	case 'L':
	case '[':stack.pushRef(slots->getRef(slotId)); break;
	default:
		break;
	}

}

