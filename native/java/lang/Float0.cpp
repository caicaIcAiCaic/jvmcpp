#include"Float0.h"

void Float0::floatToRawIntBits(Frame* frame)
{
	float value = frame->localVariablesTable.getFloat(0);
	char* fp = (char*)&value;
	frame->operandStack.pushInt(*(int*)fp);
}

void Float0::intBitsToFloat(Frame* frame)
{
	int value = frame->localVariablesTable.getInt(0);
	char* ip = (char*)&value;
	frame->operandStack.pushFloat(*(float*)ip);
}