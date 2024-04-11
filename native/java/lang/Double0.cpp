#include"Double0.h"

void Double0::doubleToRawLongBits(Frame* frame)
{
	double value = frame->localVariablesTable.getDouble(0);
	char* dp = (char*)&value;
	frame->operandStack.pushLong(*(long long*)dp);
}

void Double0::longBitsToDouble(Frame* frame)
{
	long long value = frame->localVariablesTable.getLong(0);
	char* lp = (char*)&value;
	frame->operandStack.pushDouble(*(double*)lp);
}

