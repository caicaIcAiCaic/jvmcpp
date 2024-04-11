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
	
	if (ref == NULL)	//��������������null����ֱ�ӽ�0�˳�����ջ����
	{
		stack.pushInt(0);
		return;
	}

	//�����������ò���null�����ж϶����Ƿ������ʵ���������жϽ�����������ջ
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
	stack.pushRef(ref);		//���ı������ջ��״̬

	if (ref == NULL)	//null����ת�����κ�����
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


