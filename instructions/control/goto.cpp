#include"goto.h"
#include"..\base\base_logic.h"

void GOTO::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//���ֽ����ж�ȡ2�ֽ�����
}
void GOTO::execute(Frame* frame)
{
	BaseLogic::branch(frame, offset);
}