#pragma once
#include"../base/instruction.h"

//invoke_specialָ�����ڵ���ʵ��������<init>������˽�з����͸����еķ���
//˽�з����͹��캯������Ҫ��̬���ɣ�����invoke_special���Լӿ췽�����õ��ٶ�
//��Σ�super�ؼ��ֵ��õķ�������ʹ��ʹ��invoke_virtualָ��
class INVOKE_SPECIAL :public Instruction
{
	//hack!
private:
	unsigned int index;	//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

