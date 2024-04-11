#include"System0.h"
#include"../../../rtda/heap/class.h"

void System0::arraycopy(Frame* frame)
{
	//�ȴӾֲ����������õ�5��������Դ�����Ŀ�����鲻����null
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

	//Դ�����Ŀ�����������ݲ��ܿ���
	if (!checkArrayCopy(src, dest))
	{
		cout << "java.lang.ArrayStoreException" << endl;
		exit(0);
	}

	//���srcPos��destPos��length����
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
	//����ȷ��src��dest�������飬Ȼ������������
	//������߶����������飬����Կ������������߱�������ͬ���͵Ļ�����������
	Class* srcClass = src->getClass();
	Class* destClass = dest->getClass();

	if (!srcClass->isArray() || !destClass->isArray()) return false;
	if (srcClass->componentClass()->isPrimitive() ||
		destClass->componentClass()->isPrimitive()) return srcClass == destClass;
	return true;
}

