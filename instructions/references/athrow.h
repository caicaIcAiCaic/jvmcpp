#pragma once
#include"../base/instruction.h"

//����Java������淶��athrowָ��Ӳ�����ջ�е���objectref��objectref������
//�����������͡���������Throwable����Throwable�����ʵ����֮���ڷ������쳣�����
//�в�����Ӧ��handler

class ATHROW :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	//Ѱ�Ҳ���ת���쳣�������
	bool findAndGotoExceptionHandler(Thread* t, Object* ex);
	//���������Java�����ջ�����Ҳ����쳣������룬���ӡJava�����ջ��Ϣ
	void handleUncaughtException(Thread* t, Object* ex);
};


