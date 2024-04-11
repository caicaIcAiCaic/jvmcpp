#include"iinc.h"

void IINC::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint8();
	_const = reader->readInt8();
}
void IINC::execute(Frame* frame)
{
	int val = frame->localVariablesTable.getInt(index);
	val += _const;
	frame->localVariablesTable.setInt(index, val);
}
void IINC::setIndex(unsigned int _i)
{
	index = _i;
}
void IINC::setConst(int _c)
{
	_const = _c;
}

