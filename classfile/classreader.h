#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef unsigned int u4;	//占4字节
typedef unsigned short u2;	//占2字节
typedef unsigned char u1;	//占1字节

//该类帮助我们读取class文件的数据
class ClassReader
{
private:
	vector<u1> bytearray;
	int pos;	//标志已经读取过的字节

public:
	explicit ClassReader(vector<u1>& bytes);	//构造函数，提供class文件的字节流

	u1 readU1();	//读取1个字节

	u2 readU2();	//读取2个字节

	u4 readU4();	//读取4个字节

	float readFloat();	//读取浮点类型

	long long readLong();	//读取long类型

	double readDouble();	//读取double类型

	//这里传进来的length要包括最后一个‘/0’结束符
	void readBytes(u1* buf,u4 length);	//CONSTANT_UTF8_INFO中读取char数组时，读取指定长度的字节

	vector<u2> readU2s(u2 length);	//读取指定长度的2个字节
};