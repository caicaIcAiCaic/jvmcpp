#include"invokespecial.h"
#include"../../rtda/heap/class.h"
#include"../base/base_logic.h"

void INVOKE_SPECIAL::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}
void INVOKE_SPECIAL::execute(Frame* frame)
{
	//�����õ���ǰ�ࡢ����ʱ�����ء������������ã��ڽ����������õõ����������������ڵ���
	Class* currentClass = frame->method->getClass();
	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();
	MethodRefInfo* methodRef = (MethodRefInfo*)rtcp->getConstant(index);
	Class* resolvedClass = methodRef->resolvedClass();
	Method* resolvedMethod = methodRef->resolvedMethod();

	if (resolvedMethod->getName() == "<init>" && resolvedMethod->getClass() != resolvedClass)
	{
		cout << "java.lang.NoSuchMethodError" << endl;
		exit(0);		//�������������C�ͷ���M����M�ǹ��췽����������M���������C
	}
	if (resolvedMethod->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	//�Ӳ�����ջ�е���this���ã����this����Ϊnull�����׳��쳣
	//���ݷ�������֮ǰ�����ƻ�������ջ��״̬
	Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->getArgSlotCount() - 1);
	if (ref == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	//ȷ��protected����ֻ�ܱ������÷��������������ã��Լ���ͬһ�����е������
	if (resolvedMethod->isProtected() && currentClass->isSubClassOf(resolvedMethod->getClass()) &&
		resolvedMethod->getClass()->getPackageName() != currentClass->getPackageName() &&
		ref->getClass() != currentClass && !ref->getClass()->isSubClassOf(currentClass))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	//������õ��ǳ����еĺ������Ҳ��ǹ��캯�����ҵ�ǰ�౻ACC_SUPER���
	//���ڸ��������ϲ�������Ҫ���õķ���
	Method* methodToBeInvoked = resolvedMethod;
	if (currentClass->isSuper() &&
		currentClass->isSubClassOf(resolvedClass) &&
		resolvedMethod->getName() != "<init>")
	{
		methodToBeInvoked = MethodRefInfo::lookupMethodInClass(currentClass->getSuperClass(), methodRef->name, methodRef->descriptor);
	}

	//�������ʧ�ܻ��߷����ǳ���ģ����ų��쳣
	if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract())
	{
		cout << "java.lang.AbstractMethodError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, methodToBeInvoked);
}



