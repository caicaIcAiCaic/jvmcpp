#include "invokevirtual.h"
#include "../../rtda/heap/string_pool.h"
#include "../base/base_logic.h"

void INVOKE_VIRTUAL::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void INVOKE_VIRTUAL::execute(Frame* frame)
{
	Class* currentClass = frame->method->getClass();
	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();
	MethodRefInfo* methodRef = (MethodRefInfo*)rtcp->getConstant(index);
	Method* resolvedMethod = methodRef->resolvedMethod();   // ����ʱ�������е��������������

	if (resolvedMethod->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->getArgSlotCount() - 1);
	if (ref == nullptr)
	{
		// ��ȻҪ��hack�ķ�ʽ����system.out.println()
		// ��Ϊprintln��Ҫд�ı��ط���̫������
		if (methodRef->name == "println") {
			_println(frame, methodRef->descriptor);
			return;
		}
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	if (resolvedMethod->isProtected() && currentClass->isSubClassOf(resolvedMethod->getClass()) &&
		resolvedMethod->getClass()->getPackageName() != currentClass->getPackageName() &&
		ref->getClass() != currentClass && !ref->getClass()->isSubClassOf(currentClass))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}
	//���������invoke_special�еĴ�����ͬ

	Method* methodToBeInvoked = MethodRefInfo::lookupMethodInClass(ref->getClass(),
		methodRef->name, methodRef->descriptor);
	if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract())
	{
		cout << "java.lang.AbstractMethodError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, methodToBeInvoked);
}

void INVOKE_VIRTUAL::_println(Frame* frame, string descriptor)
{
	OperandStack& stack = frame->operandStack;
	if (descriptor == "(Z)V") cout << std::boolalpha << (stack.popInt() != 0) << endl;
	else if (descriptor == "(C)V") cout << stack.popInt() << endl;
	else if (descriptor == "(B)V") cout << stack.popInt() << endl;
	else if (descriptor == "(S)V") cout << stack.popInt() << endl;
	else if (descriptor == "(I)V") cout << stack.popInt() << endl;
	else if (descriptor == "(J)V") cout << stack.popLong() << endl;
	else if (descriptor == "(F)V") cout << stack.popFloat() << endl;
	else if (descriptor == "(D)V") cout << stack.popDouble() << endl;
	else if (descriptor == "(Ljava/lang/String;)V")
	{
		Object* jStr = stack.popRef();
		string cppStr = StringPool::cppString(jStr);
		cout << cppStr << endl;
	}
	else {
		//frame->revertNextPC();
		//Object* obj = stack.popRef();
		//stack.pushRef(obj);
		//Method* m = obj->getClass()->getMethod("toString", "()Ljava/lang/String;",false);
		//BaseLogic::invokeMethod(frame, m);
		cout << "println��" << descriptor << endl;
		exit(0);
	}
	stack.popRef();
}

