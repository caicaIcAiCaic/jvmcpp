#include"invokeinterface.h"
#include"../../rtda/heap/class.h"
#include"../base/base_logic.h"

void INVOKE_INTERFACE::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
	argSlotCount = reader->readUint8();
	reader->readUint8();	//这一个字节必须是0
}

void INVOKE_INTERFACE::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	InterfaceMethodRefInfo* methodRef = (InterfaceMethodRefInfo*)rtcp->getConstant(index);
	Method* resolvedMethod = methodRef->resolvedInterfaceMethod();

	if (resolvedMethod->isStatic() || resolvedMethod->isPrivate())
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;	//不兼容!
		exit(0);
	}

	//得到this引用
	Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->getArgSlotCount() - 1);
	if (ref == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	//如果this引用所指向的类没有实现接口方法引用所指向的接口，则抛出异常
	if (!ref->getClass()->isImplements(methodRef->resolvedClass()))
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;	//不兼容!
		exit(0);
	}

	Method* methodToBeInvoked = MethodRefInfo::lookupMethodInClass(ref->getClass(),
		methodRef->name, methodRef->descriptor);
	if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract())
	{
		cout << "java.lang.AbstractMethodError" << endl;
		exit(0);
	}
	if (!methodToBeInvoked->isPublic())	//如果找到的方法不是public，则抛出异常
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, methodToBeInvoked);
}