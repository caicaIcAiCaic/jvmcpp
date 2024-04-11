#include"goto.h"
#include"..\base\base_logic.h"

void GOTO::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//从字节码中读取2字节整数
}
void GOTO::execute(Frame* frame)
{
	BaseLogic::branch(frame, offset);
}