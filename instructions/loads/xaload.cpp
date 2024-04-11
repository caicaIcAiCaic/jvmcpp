#include"xaload.h"

void AALOAD::fetchOperands(BytecodeReader* reader)
{

}
void AALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	int index = stack.popInt();
	Object* arrRef = stack.popRef();

	if (arrRef == nullptr)
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
	stack.pushRef(refs[index]);
}


void BALOAD::fetchOperands(BytecodeReader* reader)
{

}
void BALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushInt(refs[index]);
}


void CALOAD::fetchOperands(BytecodeReader* reader)
{

}
void CALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushInt(refs[index]);
}


void DALOAD::fetchOperands(BytecodeReader* reader)
{

}
void DALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushDouble(refs[index]);
}


void FALOAD::fetchOperands(BytecodeReader* reader)
{

}
void FALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushFloat(refs[index]);
}


void IALOAD::fetchOperands(BytecodeReader* reader)
{

}
void IALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushInt(refs[index]);
}


void LALOAD::fetchOperands(BytecodeReader* reader)
{

}
void LALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushLong(refs[index]);
}


void SALOAD::fetchOperands(BytecodeReader* reader)
{

}
void SALOAD::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
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
	stack.pushInt(refs[index]);
}

