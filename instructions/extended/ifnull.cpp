#include"ifnull.h"
#include"..\base\base_logic.h"

void IFNULL::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFNULL::execute(Frame* frame)
{
	void* val = frame->operandStack.popRef();
	if (val == nullptr)
	{
		BaseLogic::branch(frame, offset);
	}
}

void IFNONNULL::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void IFNONNULL::execute(Frame* frame)
{
	void* val = frame->operandStack.popRef();
	if (val != nullptr)
	{
		BaseLogic::branch(frame, offset);
	}
}
