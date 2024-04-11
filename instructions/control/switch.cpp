#include"switch.h"
#include"../base/base_logic.h"

void TABLE_SWITCH::fetchOperands(BytecodeReader* reader)
{
	reader->skipPadding();		//��������ֽ�
	defaultOffset = reader->readInt32();
	low = reader->readInt32();
	high = reader->readInt32();
	jumpOffsetsCount = high - low + 1;
	jumpOffsets = reader->readInt32s(jumpOffsetsCount);
}
void TABLE_SWITCH::execute(Frame* frame)
{
	int index = frame->operandStack.popInt();
	int offset = 0;
	if (index >= low && index <= high)
	{
		offset = jumpOffsets[index - low];  //��ָ��ֱ�Ӱ���˳����Ҽ���
	}
	else
	{
		offset = defaultOffset;
	}
	BaseLogic::branch(frame, offset);
}


void LOOKUP_SWITCH::fetchOperands(BytecodeReader* reader)
{
	reader->skipPadding();	//��������ֽ�
	defaultOffset = reader->readInt32();
	npairs = reader->readInt32();
	matchOffsets = reader->readInt32s(npairs * 2);
}
void LOOKUP_SWITCH::execute(Frame* frame)
{
	int key = frame->operandStack.popInt();
	for (int i = 0; i < npairs * 2; i += 2) //������ת���е���
	{
		if (matchOffsets[i] == key)
		{
			int offset = matchOffsets[i + 1];
			BaseLogic::branch(frame, offset);
			return;
		}
	}
	BaseLogic::branch(frame, defaultOffset);
}
