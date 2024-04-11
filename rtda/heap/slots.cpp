#include"slots.h"

Slots::Slots(unsigned int s)
{
	staticSlotCount = s;
	slots = vector<slot>(staticSlotCount);
}


void Slots::setInt(unsigned int index, int val)
{
	slot value;
	value.bytes[3] = val & 0xff;
	value.bytes[2] = val >> 8 & 0xff;
	value.bytes[1] = val >> 16 & 0xff;
	value.bytes[0] = val >> 24 & 0xff;
	slots[index] = value;
}
int Slots::getInt(unsigned int index)
{
	slot value = slots[index];
	return (int)((value.bytes[0] << 24) + (value.bytes[1] << 16)
		+ (value.bytes[2] << 8) + value.bytes[3]);
}
void Slots::setFloat(unsigned int index, float val)
{
	slot value;
	unsigned char* fp = (unsigned char*)(&val);
	value.bytes[0] = fp[0];
	value.bytes[1] = fp[1];
	value.bytes[2] = fp[2];
	value.bytes[3] = fp[3];
	slots[index] = value;
}
float Slots::getFloat(unsigned int index)
{
	slot value = slots[index];
	float* fp = (float*)value.bytes;
	return *fp;
}

void Slots::setLong(unsigned int index, long long val)	//64λ
{
	slot value_higher, value_lower;	//分别声明高位、低位;高位在前
	value_lower.bytes[3] = val & 0xff;
	value_lower.bytes[2] = val >> 8 & 0xff;
	value_lower.bytes[1] = val >> 16 & 0xff;
	value_lower.bytes[0] = val >> 24 & 0xff;

	value_higher.bytes[3] = val >> 32 & 0xff;
	value_higher.bytes[2] = val >> 40 & 0xff;
	value_higher.bytes[1] = val >> 48 & 0xff;
	value_higher.bytes[0] = val >> 56 & 0xff;

	slots[index] = value_higher;
	slots[index + 1] = value_lower;
}

long long Slots::getLong(unsigned int index)
{
	slot value_higher = slots[index];
	slot value_lower = slots[index + 1];
	return (long long)(((long long)value_higher.bytes[0] << 56) + ((long long)value_higher.bytes[1] << 48)
		+ ((long long)value_higher.bytes[2] << 40) + ((long long)value_higher.bytes[3] << 32)
		+ ((long long)value_lower.bytes[0] << 24) + ((long long)value_lower.bytes[1] << 16)
		+ ((long long)value_lower.bytes[2] << 8) + value_lower.bytes[3]);
}

void Slots::setDouble(unsigned int index, double val)
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

	slots[index] = value_higher;
	slots[index + 1] = value_lower;
}
double Slots::getDouble(unsigned int index)
{
	slot value_higher = slots[index], value_lower = slots[index + 1];
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

void Slots::setRef(unsigned int index, Object* val)
{
	slot value;
    value.ref = val;
//	value.bytes[3] = (int)val & 0xff;
//	value.bytes[2] = (int)val >> 8 & 0xff;
//	value.bytes[1] = (int)val >> 16 & 0xff;
//	value.bytes[0] = (int)val >> 24 & 0xff;
	slots[index] = value;
}

Object* Slots::getRef(unsigned int index)
{
	slot value = slots[index];
//	return (Object*)((value.bytes[0] << 24) + (value.bytes[1] << 16)
//		+ (value.bytes[2] << 8) + value.bytes[3]);
    return value.ref;
}