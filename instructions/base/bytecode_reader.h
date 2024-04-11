#pragma once
#include<vector>

using std::vector;

//该列用来解析指令，从code字节流中依次生成指令
class BytecodeReader
{
private:
	unsigned char* code = nullptr;	//存放字节码
	unsigned int code_length = 0;
	int pc = 0;	//它指向目前执行到code中的第几个字节
public:
	//避免每次解析指令都创建一个实例
	void reSet(unsigned char* _code, unsigned int _code_length, int _pc);

	unsigned char readUint8();	//读取无符号8位int，即1字节
	char readInt8();			//读取有符号8位int

	unsigned short readUint16();
	short readInt16();

	int readInt32();

	vector<int> readInt32s(int n);

	void skipPadding();	//用来跳过填充；只有tableswitch和lookupswitch指令使用

	int getPC();
	void setPC(int _pc);
};