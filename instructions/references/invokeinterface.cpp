#include"invokeinterface.h"
#include"../../rtda/heap/class.h"
#include"../base/base_logic.h"

void INVOKE_INTERFACE::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
	argSlotCount = reader->readUint8();
	reader->readUint8();	//��һ���ֽڱ�����0
}

void INVOKE_INTERFACE::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	InterfaceMethodRefInfo* methodRef = (InterfaceMethodRefInfo*)rtcp->getConstant(index);
	Method* resolvedMethod = methodRef->resolvedInterfaceMethod();

	if (resolvedMethod->isStatic() || resolvedMethod->isPrivate())
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;	//������!
		exit(0);
	}

	//�õ�this����
	Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->getArgSlotCount() - 1);
	if (ref == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	//���this������ָ�����û��ʵ�ֽӿڷ���������ָ��Ľӿڣ����׳��쳣
	if (!ref->getClass()->isImplements(methodRef->resolvedClass()))
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;	//������!
		exit(0);
	}

	Method* methodToBeInvoked = MethodRefInfo::lookupMethodInClass(ref->getClass(),
		methodRef->name, methodRef->descriptor);
	if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract())
	{
		cout << "java.lang.AbstractMethodError" << endl;
		exit(0);
	}
	if (!methodToBeInvoked->isPublic())	//����ҵ��ķ�������public�����׳��쳣
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, methodToBeInvoked);
}