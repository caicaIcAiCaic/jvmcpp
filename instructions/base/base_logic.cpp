#include"base_logic.h"
#include"..\..\rtda\heap\string_pool.h"
#include"..\..\rtda\thread.h"

void BaseLogic::branch(Frame* frame, int offset)
{
	int pc = frame->thread->getPC();
	frame->setNextPC(pc + offset);
}

void BaseLogic::_ldc(Frame* frame, unsigned int index)
{
	OperandStack& stack = frame->operandStack;
	Class* _class = frame->method->getClass();
	RunTimeConstantPool* rtcp =	_class->getRunTimeConstantPool();
	Constant* c = rtcp->getConstant(index);

	switch (c->tag)
	{
	case 3:stack.pushInt(((IntInfo*)c)->value); break;
	case 4:stack.pushFloat(((FloatInfo*)c)->value); break;
	case 8:stack.pushRef(StringPool::JString(_class->getClassLoader(), ((StringInfo*)c)->value));
		break;
		//�������ʱ�������еĳ����������ã��������������Ӧ��java/lang/Class��������ջ��
	case 7:stack.pushRef(((ClassRefInfo*)c)->resolvedClass()->getJClass()); break;
	default:
		cout << "tode:ldc!" << endl;
		exit(0);
	}
}

void BaseLogic::invokeMethod(Frame* invokerFrame, Method* method)
{
	Thread* t = invokerFrame->thread;
	Frame* f = new Frame(method,t);
	t->pushFrame(f);		//�����µ�ջ֡������Java�����ջ

	//ȷ�������Ĳ����ھֲ���������ռ�ö���λ�ã��������������һ�����ڴ�Java�����п����Ĳ�������
	//1��long��double���͵Ĳ���Ҫռ������slot
	//2������ʵ��������Java���������Զ������this�����������б��ײ�
	//����ʵ�ʵĲ���ռ��n��λ�ã����ΰ���n�������ӵ����ߵĲ�����ջ�е��������뱻�������ľֲ��������У��������ݾ������
	int argSlotSlot = int(method->getArgSlotCount());
	if (argSlotSlot > 0)
	{
		for (int i = argSlotSlot - 1; i >= 0; i--)
		{
			slot s = invokerFrame->operandStack.popSlot();
			f->localVariablesTable.setSlot((unsigned int)i, s);
		}
	}

	//hack!Ŀǰ����֧�ֱ��ط����ĵ��ã�Object������һ�����ط�����registerNatives()
	//Ϊ����Java�����������Ҫ�����÷����Լ������ı��ط���
	//if (method->isNative())
	//{
	//	if (method->getName() == "registerNatives") t->popFrame();
	//	else
	//	{
	//		cout << method->getClass()->getName() << "." << method->getName() << "  " << method->getDescriptor() << endl;
	//		exit(0);
	//	}
	//}
}

void BaseLogic::initClass(Thread* t, Class* c)
{
	c->StartInit();
	scheduleClinit(t, c);   //�ȵ��������clinit��������Ϊ��������ջ֡�����棬����ִ�е���
	initSuperClass(t, c);
}

void BaseLogic::scheduleClinit(Thread* t, Class* c)
{
	Method* clinit = c->getClinitMethod();
	if (clinit != nullptr)
	{
		//excute
		Frame* frame = new Frame(clinit,t);
		t->pushFrame(frame);
	}
}

void BaseLogic::initSuperClass(Thread* t, Class* c)
{
	if (!c->isInterface())
	{
		Class* superClass = c->getSuperClass();
		if (superClass != nullptr && !superClass->InitStarted()) initClass(t, superClass);
	}
}


