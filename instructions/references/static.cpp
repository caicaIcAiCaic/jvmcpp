#include"static.h"
#include"../../rtda/heap/class.h"
#include "../base/base_logic.h"

void PUT_STATIC::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void PUT_STATIC::execute(Frame* frame)
{
	Method* currentMethod = frame->method;	//���ȵõ���ǰ�����뷽��
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//�õ���ǰ������ʱ������
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);	
	Field* field = fieldRef->resolvedField();	//������������
	Class* c = field->getClass();	//�õ��ֶ����ڵ���

	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	//�����������ֶ���ʵ���ֶζ��Ǿ�̬�ֶΣ����׳��쳣
	//�����final�ֶΣ���̬����������ֻ�������ʼ�������и�����ֵ
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

	//�����ֶ����ʹӲ�����ջ�е�����Ӧ��ֵ��Ȼ�󸳸���̬����
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
	Method* currentMethod = frame->method;	//���ȵõ���ǰ�����뷽��
	Class* currentClass = currentMethod->getClass();

	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();	//�õ���ǰ������ʱ������
	FieldRefInfo* fieldRef = (FieldRefInfo*)rtcp->getConstant(index);
	Field* field = fieldRef->resolvedField();	//������������
	Class* c = field->getClass();	//�õ��ֶ����ڵ���

	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	//�����������ֶ���ʵ���ֶζ��Ǿ�̬�ֶΣ����׳��쳣
	//getstaicֻ�Ƕ�ȡ��̬�ֶε�ֵ������Ҫ�����Ƿ�Ϊfinal����
	if (!field->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangError" << endl;
		exit(0);
	}

	//�����ֶ����ʹӲ�����ջ�е�����Ӧ��ֵ��Ȼ�󸳸���̬����
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