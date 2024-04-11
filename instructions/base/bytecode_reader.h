#pragma once
#include<vector>

using std::vector;

//������������ָ���code�ֽ�������������ָ��
class BytecodeReader
{
private:
	unsigned char* code = nullptr;	//����ֽ���
	unsigned int code_length = 0;
	int pc = 0;	//��ָ��Ŀǰִ�е�code�еĵڼ����ֽ�
public:
	//����ÿ�ν���ָ�����һ��ʵ��
	void reSet(unsigned char* _code, unsigned int _code_length, int _pc);

	unsigned char readUint8();	//��ȡ�޷���8λint����1�ֽ�
	char readInt8();			//��ȡ�з���8λint

	unsigned short readUint16();
	short readInt16();

	int readInt32();

	vector<int> readInt32s(int n);

	void skipPadding();	//����������䣻ֻ��tableswitch��lookupswitchָ��ʹ��

	int getPC();
	void setPC(int _pc);
};