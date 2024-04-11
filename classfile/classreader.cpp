#include"classreader.h"

ClassReader::ClassReader(vector<u1>& bytes):pos(0)
{
	bytearray = bytes;
}

u1 ClassReader::readU1()
{
	return bytearray[pos++];
}

u2 ClassReader::readU2()
{
	u1 temp[2];
	temp[0] = bytearray[pos++];
	temp[1] = bytearray[pos++];
	return (u2)((temp[0] << 8) + temp[1]);
}

u4 ClassReader::readU4()
{
	u1 temp[4];
	temp[0] = bytearray[pos++];
	temp[1] = bytearray[pos++];
	temp[2] = bytearray[pos++];
	temp[3] = bytearray[pos++];
	return (u4)((temp[0] << 24) + (temp[1] << 16) + (temp[2] << 8) + temp[3]);
}

float ClassReader::readFloat()
{
	u1 temp[4];
	temp[3] = bytearray[pos++];
	temp[2] = bytearray[pos++];
	temp[1] = bytearray[pos++];
	temp[0] = bytearray[pos++];
	float* p = (float*)temp;
	return *p;
}

long long ClassReader::readLong()
{
	u1 temp[8];
	temp[0] = bytearray[pos++];
	temp[1] = bytearray[pos++];
	temp[2] = bytearray[pos++];
	temp[3] = bytearray[pos++];
	temp[4] = bytearray[pos++];
	temp[5] = bytearray[pos++];
	temp[6] = bytearray[pos++];
	temp[7] = bytearray[pos++];
	return (long long)(((long long)temp[0] << 56) + ((long long)temp[1] << 48)
		+ ((long long)temp[2] << 40) + ((long long)temp[3] << 32) + ((long long)temp[4] << 24)
		+ ((long long)temp[5] << 16) + ((long long)temp[6] << 8) + temp[7]);
}

double ClassReader::readDouble()
{
	u1 temp[8];
	temp[7] = bytearray[pos++];
	temp[6] = bytearray[pos++];
	temp[5] = bytearray[pos++];
	temp[4] = bytearray[pos++];
	temp[3] = bytearray[pos++];
	temp[2] = bytearray[pos++];
	temp[1] = bytearray[pos++];
	temp[0] = bytearray[pos++];
	double* p = (double*)temp;
	return *p;
}

void ClassReader::readBytes(u1* buf,u4 length)	//CONSTANT_UTF8_INFO中读取char数组时
{
	for (int i = 0; i < length - 1; i++)
	{
		buf[i] = readU1();
	}
	buf[length - 1] = '\0';
}

vector<u2> ClassReader::readU2s(u2 length)
{
	vector<u2> temp(length);
	for (int i = 0; i < length; i++)
	{
		temp[i] = readU2();
	}
	return temp;
}
