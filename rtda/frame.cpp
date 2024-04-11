#include"thread.h"

LocalVars::LocalVars(unsigned int s):maxSize(s)
{
	localVarTable = vector<slot>(maxSize);
}

void LocalVars::setSlot(unsigned int index, slot s)
{
	localVarTable[index] = s;
}

void LocalVars::setInt(unsigned int index, int val)
{
    localVarTable[index].bytes[3] = val & 0xff;
    localVarTable[index].bytes[2] = val >> 8 & 0xff;
    localVarTable[index].bytes[1] = val >> 16 & 0xff;
    localVarTable[index].bytes[0] = val >> 24 & 0xff;
}
int LocalVars::getInt(unsigned int index)
{
	return (int)((localVarTable[index].bytes[0] << 24) + (localVarTable[index].bytes[1] << 16)
		+ (localVarTable[index].bytes[2] << 8) + localVarTable[index].bytes[3]);
}
void LocalVars::setFloat(unsigned int index, float val)
{
	unsigned char* fp = (unsigned char*)(&val);
    localVarTable[index].bytes[0] = fp[0];
    localVarTable[index].bytes[1] = fp[1];
    localVarTable[index].bytes[2] = fp[2];
    localVarTable[index].bytes[3] = fp[3];
}
float LocalVars::getFloat(unsigned int index)
{
	float* fp = (float*)localVarTable[index].bytes;
	return *fp;
}

void LocalVars::setLong(unsigned int index, long long val)	//64λ
{
	slot value_higher, value_lower;	//分别声明高位、低位;高位在前
    localVarTable[index + 1].bytes[3] = val & 0xff;
    localVarTable[index + 1].bytes[2] = val >> 8 & 0xff;
    localVarTable[index + 1].bytes[1] = val >> 16 & 0xff;
    localVarTable[index + 1].bytes[0] = val >> 24 & 0xff;

    localVarTable[index].bytes[3] = val >> 32 & 0xff;
    localVarTable[index].bytes[2] = val >> 40 & 0xff;
    localVarTable[index].bytes[1] = val >> 48 & 0xff;
    localVarTable[index].bytes[0] = val >> 56 & 0xff;
}

long long LocalVars::getLong(unsigned int index)
{
	slot value_higher = localVarTable[index];
	slot value_lower = localVarTable[index + 1];
	return (long long)(((long long)value_higher.bytes[0] << 56) + ((long long)value_higher.bytes[1] << 48)
		+ ((long long)value_higher.bytes[2] << 40) + ((long long)value_higher.bytes[3] << 32)
		+ ((long long)value_lower.bytes[0] << 24) + ((long long)value_lower.bytes[1] << 16)
		+ ((long long)value_lower.bytes[2] << 8) + value_lower.bytes[3]);
}

void LocalVars::setDouble(unsigned int index, double val)
{
	slot value_higher, value_lower;	//分别声明高位、低位;高位在前
	unsigned char* fp = (unsigned char*)(&val);
    localVarTable[index].bytes[0] = fp[0];
    localVarTable[index].bytes[1] = fp[1];
    localVarTable[index].bytes[2] = fp[2];
    localVarTable[index].bytes[3] = fp[3];

    localVarTable[index + 1].bytes[0] = fp[4];
    localVarTable[index + 1].bytes[1] = fp[5];
    localVarTable[index + 1].bytes[2] = fp[6];
    localVarTable[index + 1].bytes[3] = fp[7];
}
double LocalVars::getDouble(unsigned int index)
{
	unsigned char bytes[8];
	bytes[0] = localVarTable[index].bytes[0];
	bytes[1] = localVarTable[index].bytes[1];
	bytes[2] = localVarTable[index].bytes[2];
	bytes[3] = localVarTable[index].bytes[3];
	bytes[4] = localVarTable[index + 1].bytes[0];
	bytes[5] = localVarTable[index + 1].bytes[1];
	bytes[6] = localVarTable[index + 1].bytes[2];
	bytes[7] = localVarTable[index + 1].bytes[3];
	double* dp = (double*)bytes;
	return *dp;
}

void LocalVars::setRef(unsigned int index, Object* val)
{
    localVarTable[index].ref = val;
}

Object* LocalVars::getRef(unsigned int index)
{
    return localVarTable[index].ref;
}


OperandStack::OperandStack(unsigned int mS):maxSize(mS)
{

}
void OperandStack::Clear()
{
	operandStack.clear();
}

void OperandStack::pushSlot(slot _slot)
{
	operandStack.push_back(_slot);
}

slot OperandStack::popSlot()
{
	slot value = operandStack.back();
	operandStack.pop_back();
	return value;
}

void OperandStack::pushInt(int val)
{
	slot value;
	value.bytes[3] = val & 0xff;
	value.bytes[2] = val >> 8 & 0xff;
	value.bytes[1] = val >> 16 & 0xff;
	value.bytes[0] = val >> 24 & 0xff;
	operandStack.push_back(value);
}
int OperandStack::popInt()
{
	slot value = operandStack.back();
	operandStack.pop_back();
	return (int)((value.bytes[0] << 24) + (value.bytes[1] << 16)
		+ (value.bytes[2] << 8) + value.bytes[3]);
}

void OperandStack::pushFloat(float val)
{
	slot value;
	unsigned char* fp = (unsigned char*)(&val);
	value.bytes[0] = fp[0];
	value.bytes[1] = fp[1];
	value.bytes[2] = fp[2];
	value.bytes[3] = fp[3];
	operandStack.push_back(value);
}

float OperandStack::popFloat()
{
	slot value = operandStack.back();
	operandStack.pop_back();
	float* fp = (float*)value.bytes;
	return *fp;
}

void OperandStack::pushLong(long long val)
{
	slot value_higher, value_lower;
	value_lower.bytes[3] = val & 0xff;
	value_lower.bytes[2] = val >> 8 & 0xff;
	value_lower.bytes[1] = val >> 16 & 0xff;
	value_lower.bytes[0] = val >> 24 & 0xff;

	value_higher.bytes[3] = val >> 32 & 0xff;
	value_higher.bytes[2] = val >> 40 & 0xff;
	value_higher.bytes[1] = val >> 48 & 0xff;
	value_higher.bytes[0] = val >> 56 & 0xff;

	operandStack.push_back(value_higher);
	operandStack.push_back(value_lower);
}

long long OperandStack::popLong()
{
	slot value_lower = operandStack.back();
	operandStack.pop_back();
	slot value_higher = operandStack.back();
	operandStack.pop_back();
	return (long long)(((long long)value_higher.bytes[0] << 56) + ((long long)value_higher.bytes[1] << 48)
		+ ((long long)value_higher.bytes[2] << 40) + ((long long)value_higher.bytes[3] << 32)
		+ ((long long)value_lower.bytes[0] << 24) + ((long long)value_lower.bytes[1] << 16)
		+ ((long long)value_lower.bytes[2] << 8) + value_lower.bytes[3]);
}

void OperandStack::pushDouble(double val)
{
	slot value_higher, value_lower;	//分别声明高位、低位;高位在前
	unsigned char* fp = (unsigned char*)(&val);
	value_higher.bytes[0] = fp[0];
	value_higher.bytes[1] = fp[1];
	value_higher.bytes[2] = fp[2];
	value_higher.bytes[3] = fp[3];

	value_lower.bytes[0] = fp[4];
	value_lower.bytes[1] = fp[5];
	value_lower.bytes[2] = fp[6];
	value_lower.bytes[3] = fp[7];

	operandStack.push_back(value_higher);
	operandStack.push_back(value_lower);
}

double OperandStack::popDouble()
{
	slot value_lower = operandStack.back();
	operandStack.pop_back();
	slot value_higher = operandStack.back();
	operandStack.pop_back();
	unsigned char bytes[8];
	bytes[0] = value_higher.bytes[0];
	bytes[1] = value_higher.bytes[1];
	bytes[2] = value_higher.bytes[2];
	bytes[3] = value_higher.bytes[3];
	bytes[4] = value_lower.bytes[0];
	bytes[5] = value_lower.bytes[1];
	bytes[6] = value_lower.bytes[2];
	bytes[7] = value_lower.bytes[3];
	double* dp = (double*)bytes;
	return *dp;
}

void OperandStack::pushRef(Object* val)
{
	slot value;
    value.ref = val;
	operandStack.push_back(value);
}

Object* OperandStack::popRef()
{
	slot value = operandStack.back();
	operandStack.pop_back();
    return value.ref;
}

Object* OperandStack::getRefFromTop(unsigned int n)
{
	int size = operandStack.size();
    return operandStack[size - 1 - n].ref;
}

Frame::Frame(Method* m,Thread* t): localVariablesTable(m->getMaxLocals()), operandStack(m->getMaxStack()),method(m), thread(t)
{

}

unsigned int Frame::getNextPC()
{
	return nextpc;
}
void Frame::setNextPC(unsigned int _pc)
{
	nextpc = _pc;
}

void Frame::resvertNextPC()
{
	nextpc = thread->getPC();
}



