#include"goto_w.h"
#include"..\base\base_logic.h"

void GOTO_W::fetchOperands(BytecodeReader* reader)
{
	offset = int(reader->readInt16());	//���ֽ����ж�ȡ2�ֽ�����
}
void GOTO_W::execute(Frame* frame)
{
	BaseLogic::branch(frame, offset);
}