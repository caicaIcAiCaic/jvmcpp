#include"xastore.h"

void AASTORE::fetchOperands(BytecodeReader* reader)
{

}
void AASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	Object* val = stack.popRef();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	Object** refs = arrRef->getObjects();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void BASTORE::fetchOperands(BytecodeReader* reader)
{

}
void BASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int val = stack.popInt();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	char* refs = arrRef->getBytes();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void CASTORE::fetchOperands(BytecodeReader* reader)
{

}
void CASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int val = stack.popInt();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	wchar_t* refs = arrRef->getChars();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void DASTORE::fetchOperands(BytecodeReader* reader)
{

}
void DASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	double val = stack.popDouble();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	double* refs = arrRef->getDoubles();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void FASTORE::fetchOperands(BytecodeReader* reader)
{

}
void FASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	float val = stack.popFloat();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	float* refs = arrRef->getFloats();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void IASTORE::fetchOperands(BytecodeReader* reader)
{

}
void IASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int val = stack.popInt();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	int* refs = arrRef->getInts();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void LASTORE::fetchOperands(BytecodeReader* reader)
{

}
void LASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	long long val = stack.popLong();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	long long* refs = arrRef->getLongs();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}


void SASTORE::fetchOperands(BytecodeReader* reader)
{

}
void SASTORE::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int val = stack.popInt();
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == NULL)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	short* refs = arrRef->getShorts();

	if (index < 0 || index >= arrRef->getArrayLength())
	{
		cout << "ArrayIndexOutOfBoundsException" << endl;
		exit(0);
	}
	refs[index] = val;
}
