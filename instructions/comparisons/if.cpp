#include"if.h"
#include"..\base\base_logic.h"

void IFEQ::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFEQ::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val == 0)
	{
		BaseLogic::branch(frame, offset);
	}
}

void IFNE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFNE::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val != 0)
	{
		BaseLogic::branch(frame, offset);
	}
}

//x<0
void IFLT::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFLT::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val < 0)
	{
		BaseLogic::branch(frame, offset);
	}
}
//x<=0
void IFLE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFLE::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val <= 0)
	{
		BaseLogic::branch(frame, offset);
	}
}
//x>0
void IFGT::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFGT::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val > 0)
	{
		BaseLogic::branch(frame, offset);
	}
}
//x>=0
void IFGE::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFGE::execute(Frame* frame)
{
	int val = frame->operandStack.popInt();
	if (val >= 0)
	{
		BaseLogic::branch(frame, offset);
	}
}


