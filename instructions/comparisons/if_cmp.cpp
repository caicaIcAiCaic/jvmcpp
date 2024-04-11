#include"if_cmp.h"
#include"..\base\base_logic.h"

void IF_ICMPEQ::fetchOperands(BytecodeReader* reader)
{
	//跳转的偏移量
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPEQ::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 == v2)
	{
		BaseLogic::branch(frame, offset);
	}
}


void IF_ICMPNE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPNE::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 != v2)
	{
		BaseLogic::branch(frame, offset);
	}
}

//v1 < v2
void IF_ICMPLT::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPLT::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 < v2)
	{
		BaseLogic::branch(frame, offset);
	}
}

//v1 <= v2
void IF_ICMPLE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPLE::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 <= v2)
	{
		BaseLogic::branch(frame, offset);
	}
}

//v1 > v2
void IF_ICMPGT::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPGT::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 > v2)
	{
		BaseLogic::branch(frame, offset);
	}
}


//v1 >= v2
void IF_ICMPGE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ICMPGE::execute(Frame* frame)
{
	int v2 = frame->operandStack.popInt();
	int v1 = frame->operandStack.popInt();
	if (v1 >= v2)
	{
		BaseLogic::branch(frame, offset);
	}
}



void IF_ACMPEQ::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ACMPEQ::execute(Frame* frame)
{
	void* v2 = frame->operandStack.popRef();
	void* v1 = frame->operandStack.popRef();
	if (v1 == v2)
	{
		BaseLogic::branch(frame, offset);
	}
}

void IF_ACMPNE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IF_ACMPNE::execute(Frame* frame)
{
	void* v2 = frame->operandStack.popRef();
	void* v1 = frame->operandStack.popRef();
	if (v1 != v2)
	{
		BaseLogic::branch(frame, offset);
	}
}