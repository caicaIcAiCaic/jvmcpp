#include"System0.h"
#include"../../../rtda/heap/class.h"

void System0::arraycopy(Frame* frame)
{
	//先从局部变量表中拿到5个参数。源数组和目标数组不能是null
	LocalVars& vars = frame->localVariablesTable;
	Object* src = vars.getRef(0);
	int srcPos = vars.getInt(1);
	Object* dest = vars.getRef(2);
	int destPos = vars.getInt(3);
	int length = vars.getInt(4);

	if (src == nullptr || dest == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	//源数组和目标数组必须兼容才能拷贝
	if (!checkArrayCopy(src, dest))
	{
		cout << "java.lang.ArrayStoreException" << endl;
		exit(0);
	}

	//检查srcPos、destPos、length参数
	if (srcPos < 0 || destPos < 0 || length < 0 || srcPos + length > src->getArrayLength() ||
		destPos + length > dest->getArrayLength())
	{
		cout << "java.lang.IndexOutOfBoundsException" << endl;
		exit(0);
	}

	Object::ArrayCopy(src, dest, srcPos, destPos, length);
}

bool System0::checkArrayCopy(Object* src, Object* dest)
{
	//首先确保src和dest都是数组，然后检查数组类型
	//如果两者都是引用数组，则可以拷贝，否则两者必须是相同类型的基本类型数组
	Class* srcClass = src->getClass();
	Class* destClass = dest->getClass();

	if (!srcClass->isArray() || !destClass->isArray()) return false;
	if (srcClass->componentClass()->isPrimitive() ||
		destClass->componentClass()->isPrimitive()) return srcClass == destClass;
	return true;
}

