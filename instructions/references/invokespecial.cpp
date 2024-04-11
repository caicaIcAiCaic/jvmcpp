#include"invokespecial.h"
#include"../../rtda/heap/class.h"
#include"../base/base_logic.h"

void INVOKE_SPECIAL::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}
void INVOKE_SPECIAL::execute(Frame* frame)
{
	//首先拿到当前类、运行时常量池、方法符号引用；在解析符号引用得到被调方法和其所在的类
	Class* currentClass = frame->method->getClass();
	RunTimeConstantPool* rtcp = currentClass->getRunTimeConstantPool();
	MethodRefInfo* methodRef = (MethodRefInfo*)rtcp->getConstant(index);
	Class* resolvedClass = methodRef->resolvedClass();
	Method* resolvedMethod = methodRef->resolvedMethod();

	if (resolvedMethod->getName() == "<init>" && resolvedMethod->getClass() != resolvedClass)
	{
		cout << "java.lang.NoSuchMethodError" << endl;
		exit(0);		//如果解析出的类C和方法M，且M是构造方法，则声明M的类必须是C
	}
	if (resolvedMethod->isStatic())
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	//从操作数栈中弹出this引用，如果this引用为null，则抛出异常
	//传递方法参数之前不能破坏操作数栈的状态
	Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->getArgSlotCount() - 1);
	if (ref == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	//确保protected方法只能被声明该方法的类或子类调用，以及被同一个包中的类调用
	if (resolvedMethod->isProtected() && currentClass->isSubClassOf(resolvedMethod->getClass()) &&
		resolvedMethod->getClass()->getPackageName() != currentClass->getPackageName() &&
		ref->getClass() != currentClass && !ref->getClass()->isSubClassOf(currentClass))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	//如果调用的是超类中的函数，且不是构造函数，且当前类被ACC_SUPER标记
	//则在父类中向上查找最终要调用的方法
	Method* methodToBeInvoked = resolvedMethod;
	if (currentClass->isSuper() &&
		currentClass->isSubClassOf(resolvedClass) &&
		resolvedMethod->getName() != "<init>")
	{
		methodToBeInvoked = MethodRefInfo::lookupMethodInClass(currentClass->getSuperClass(), methodRef->name, methodRef->descriptor);
	}

	//如果查找失败或者方法是抽象的，则排除异常
	if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract())
	{
		cout << "java.lang.AbstractMethodError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, methodToBeInvoked);
}



