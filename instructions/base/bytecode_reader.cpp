#include"bytecode_reader.h"

//避免每次解析指令都创建一个实例
void BytecodeReader::reSet(unsigned char* _code, unsigned int _code_length, int _pc)
{
	code = _code;
	code_length = _code_length;
	pc = _pc;
}

unsigned char BytecodeReader::readUint8()
{
	return code[pc++];
}
char BytecodeReader::readInt8()
{
	return char(readUint8());
}

unsigned short BytecodeReader::readUint16()
{
	unsigned char byte1 = readUint8();
	unsigned char byte2 = readUint8();
	return (unsigned short)((byte1 << 8) + byte2);
}
short BytecodeReader::readInt16()
{
	return (short)readUint16();
}

int BytecodeReader::readInt32()
{
	unsigned char byte1 = readUint8();
	unsigned char byte2 = readUint8();
	unsigned char byte3 = readUint8();
	unsigned char byte4 = readUint8();
	return (int)((byte1 << 24) + (byte2 << 16) + (byte3 << 8) + byte4);
}

vector<int> BytecodeReader::readInt32s(int n)
{
	vector<int> ints = vector<int>(n);
	for (int i = 0; i < n; i++)
	{
		ints.push_back(readInt32());
	}
	return ints;
}
//tableswitch指令跳过padding字节
void BytecodeReader::skipPadding()
{
	while (pc % 4 != 0)
	{
		readUint8();
	}
}

int BytecodeReader::getPC()
{
	return pc;
}
void BytecodeReader::setPC(int _pc)
{
	pc = _pc;
}