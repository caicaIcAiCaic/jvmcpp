#pragma once
#include"..\..\rtda\frame.h"

//����������Ӧ��PCֵ
class BaseLogic {
public:
	static void branch(Frame* frame, int offset);
	//����������ջ��
	static void _ldc(Frame* frame, unsigned int index);
	//�ڶ�λ����Ҫ���õķ���֮��Java�����Ҫ�������������һ���µ�ջ֡����������Java�����ջ��
	static void invokeMethod(Frame* invokerFrame, Method* method);
	//��ʼ���ִࣺ��<clinit>����
	static void initClass(Thread* t, Class* c);

private:
	static void scheduleClinit(Thread* t, Class* c);
	static void initSuperClass(Thread* t, Class* c);
};


