#include"ldc.h"
#include"../base/base_logic.h"
#include"../../rtda/heap/class.h"

void LDC::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint8();
}

void LDC::execute(Frame* frame)
{
	BaseLogic::_ldc(frame, index);
}


void LDC_W::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void LDC_W::execute(Frame* frame)
{
	BaseLogic::_ldc(frame, index);
}

void LDC2_W::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void LDC2_W::execute(Frame* frame)
{
	OperandStack& stack = frame->operandStack;
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	Constant* c = rtcp->getConstant(index);

	switch (c->tag)
	{
	case 5:stack.pushLong(((LongInfo*)c)->value); break;
	case 6:stack.pushDouble(((DoubleInfo*)c)->value); break;
	default:
		cout << "tode:ldc!" << endl;
		exit(0);
	}
}

