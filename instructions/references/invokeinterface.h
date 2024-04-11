#pragma once
#include"../base/instruction.h"

//���ڵ��ýӿڷ�������������ʱ��ȷ��һ��ʵ�ָýӿڵĶ���
//invoke_interfaceָ��Ĳ�����������4�ֽڶ���2�ֽ�
//ǰ2���ֽڵĺ�����������������ָ����ͬ��ָ��������ʱ�����ص�һ������������
//��3���ֽڵ�ֵ���ٸ��������ݲ�����Ҫ��slot�����京����Method�ṹ���ж����argSlotCount�ֶ���ͬ
//����֪�������ֵ�ǿ��Ը��ݷ�������������������ģ����Ĵ��ڽ�������Ϊ��ʷԭ��
//��4���ֽ�������Oracle��ĳЩJava�����ʵ���õģ�����ֵ������0�����ֽڵĴ��ڱ�֤��Java�����������
class INVOKE_INTERFACE :public Instruction
{
	//hack!
private:
	unsigned int index;	//4�ֽ�
	unsigned int argSlotCount;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
