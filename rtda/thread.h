#pragma once
#include"frame.h"

class Thread
{
private:
	int pc;	//�൱�ڸ��̵߳ĳ��������
	vector<Frame*> JVM_Stack;	//Java�����ջ�������������Java�����ջ�����߳�˽�е�
public:
	Thread();

	int getPC();
	void setPC(int p);

	void pushFrame(Frame* frame);
	void popFrame();

	Frame* CurrentFrame();
	bool isStackEmpty();
	void ClearStack();

	vector<Frame*>& getFrames();    //��������ջ֡����Java�����ջ��
};


