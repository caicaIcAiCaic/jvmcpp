#include"static.h"
#include"../../rtda/heap/class.h"
#include "../base/base_logic.h"

void PUT_STATIC::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void PUT_STATIC::execute(Frame* frame)
{
	Method* currentMethod = frame->method;	//首先得到当前的类与方法
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//得到当前的运行时常量池
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);	
	Field* field = fieldRef->resolvedField();	//解析符号引用
	Class* c = field->getClass();	//得到字段所在的类

	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	//如果解析后的字段是实例字段而非静态字段，则抛出异常
	//如果是final字段（静态常量），则只能在类初始化方法中给他赋值
	if (!field->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangError" << endl;
		exit(0);
	}
	if (field->isFinal() && (currentClass != c || currentMethod->getName() != "<clinit>"))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	//根据字段类型从操作数栈中弹出相应的值，然后赋给静态变量
	string descriptor = field->getDescriptor();
	unsigned int slotId = field->getSlotId();
	Slots* slots = c->getStaticVars();
	OperandStack& stack = frame->operandStack;
	
	switch (descriptor[0])
	{
	case 'Z':
	case 'B':
	case 'C':
	case 'S':
	case 'I': slots->setInt(slotId, stack.popInt()); break;
	case 'F':slots->setFloat(slotId, stack.popFloat()); break;
	case 'J':slots->setLong(slotId, stack.popLong()); break;
	case 'D':slots->setDouble(slotId, stack.popDouble()); break;
	case 'L':
	case '[':slots->setRef(slotId, stack.popRef()); break;
	default:
		break;
	}
}



void GET_STATIC::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}
void GET_STATIC::execute(Frame* frame)
{
	Method* currentMethod = frame->method;	//首先得到当前的类与方法
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//得到当前的运行时常量池
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);
	Field* field = fieldRef->resolvedField();	//解析符号引用
	Class* c = field->getClass();	//得到字段所在的类

	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	//如果解析后的字段是实例字段而非静态字段，则抛出异常
	//getstaic只是读取静态字段的值，不需要考虑是否为final类型
	if (!field->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangError" << endl;
		exit(0);
	}

	//根据字段类型从操作数栈中弹出相应的值，然后赋给静态变量
	string descriptor = field->getDescriptor();
	unsigned int slotId = field->getSlotId();
	Slots* slots = c->getStaticVars();
	OperandStack& stack = frame->operandStack;

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