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
		//如果运行时常量池中的常量是类引用，则解析它，将对应的java/lang/Class对象推入栈顶
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
	t->pushFrame(f);		//创建新的栈帧并推入Java虚拟机栈

	//确定方法的参数在局部变量表中占用多少位置，但是这个数量不一定等于从Java代码中看到的参数个数
	//1、long和double类型的参数要占用两个slot
	//2、对于实例方法，Java编译器会自动的添加this引用至参数列表首部
	//假设实际的参数占据n个位置，依次把这n个变量从调用者的操作数栈中弹出，放入被调方法的局部变量表中，参数传递就完成了
	int argSlotSlot = int(method->getArgSlotCount());
	if (argSlotSlot > 0)
	{
		for (int i = argSlotSlot - 1; i >= 0; i--)
		{
			slot s = invokerFrame->operandStack.popSlot();
			f->localVariablesTable.setSlot((unsigned int)i, s);
		}
	}

	//hack!目前还不支持本地方法的调用，Object类中有一个本地方法：registerNatives()
	//为避免Java虚拟机崩溃，要跳过该方法以及其他的本地方法
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
	scheduleClinit(t, c);   //先调用子类的clinit方法，因为这样它的栈帧在下面，反而执行的晚
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


