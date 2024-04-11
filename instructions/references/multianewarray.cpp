#include"multianewarray.h"
#include"../../rtda/heap/class.h"

void MULTI_ANEW_ARRAY::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
	dimensions = reader->readUint8();

}
//�ú�������Ҫ�Ӳ�����ջ�е���n���������ֱ����ÿһ��һά����ĳ���
void MULTI_ANEW_ARRAY::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	ClassRefInfo* classRef = (ClassRefInfo*)rtcp->getConstant(index);
	Class* arrClass = classRef->resolvedClass();

	OperandStack& stack = frame->operandStack;
	vector<int> counts = popAndCheckCounts(stack, dimensions);
	Object* arr = newMultiDimensionalArray(counts,0, arrClass);
	stack.pushRef(arr);
}

vector<int> MULTI_ANEW_ARRAY::popAndCheckCounts(OperandStack& stack, int d)
{
	vector<int> counts(d);
	for (int i = d - 1; i >= 0; i--)
	{
		counts[i] = stack.popInt();
		if (counts[i] < 0)
		{
			cout << "java.lang.NegativeArraySizeException" << endl;
			exit(0);
		}
	}
	return counts;
}

Object* MULTI_ANEW_ARRAY::newMultiDimensionalArray(vector<int>& counts,int d, Class* arrClass)
{
	int count = counts[d];	//��ά������ĳ���
	Object* arr = arrClass->newArray(count);

	if (counts.size() - d > 1)
	{
		Object** refs = arr->getObjects();
		for (int i = 0; i < count; i++)
		{
			refs[i] = newMultiDimensionalArray(counts, d + 1, arrClass->componentClass());
		}
	}

	return arr;
}

