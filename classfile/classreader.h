#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef unsigned int u4;	//ռ4�ֽ�
typedef unsigned short u2;	//ռ2�ֽ�
typedef unsigned char u1;	//ռ1�ֽ�

//����������Ƕ�ȡclass�ļ�������
class ClassReader
{
private:
	vector<u1> bytearray;
	int pos;	//��־�Ѿ���ȡ�����ֽ�

public:
	explicit ClassReader(vector<u1>& bytes);	//���캯�����ṩclass�ļ����ֽ���

	u1 readU1();	//��ȡ1���ֽ�

	u2 readU2();	//��ȡ2���ֽ�

	u4 readU4();	//��ȡ4���ֽ�

	float readFloat();	//��ȡ��������

	long long readLong();	//��ȡlong����

	double readDouble();	//��ȡdouble����

	//���ﴫ������lengthҪ�������һ����/0��������
	void readBytes(u1* buf,u4 length);	//CONSTANT_UTF8_INFO�ж�ȡchar����ʱ����ȡָ�����ȵ��ֽ�

	vector<u2> readU2s(u2 length);	//��ȡָ�����ȵ�2���ֽ�
};