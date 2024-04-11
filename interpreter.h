#pragma once
#include"instructions/base/instruction.h"
#include"rtda/thread.h"
#include"rtda/heap/string_pool.h"

//����һ�����װ�Ľ�����
class Interpreter
{
private:
	bool log;	//��־�Ƿ��ӡָ��ִ����Ϣ
public:
	Interpreter(bool l);
	//interpret�����Ĳ�����MemberInfoָ�룬��һ���������������ǿ��Եõ�����code����
	void interpret(Thread* thread);
private:
	//�÷�������ݴ���Ĳ����뷵�ؾ����ָ�����
	Instruction* newInstruction(int opcode);
	//����ָ���ִ��ϸ�ڴ�ӡ������̨
	void logInstruction(Frame* frame, Instruction* inst);
};

