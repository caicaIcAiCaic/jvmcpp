#pragma once
#include"../base/instruction.h"

//�ݲ����ǽӿڵľ�̬������Ĭ�Ϸ��������Ը�ָ��ϵͳ��������Java������淶��8��Ĺ涨
//invokestaticָ�����ڵ��þ�̬����
//ͨ����̬���ɣ���������ȷ�����÷����İ汾�������ڿ�֪
class INVOKE_STATIC :public Instruction
{
private:
	unsigned int index;	//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

