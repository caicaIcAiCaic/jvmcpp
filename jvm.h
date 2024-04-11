#pragma once
#include "cmd.h"
#include "rtda/heap/class_loader.h"
#include "interpreter.h"

class JVM
{
private:
	cmd* myCmd;
	ClassPath* cp;
	ClassLoader* loader;
	Thread* mainThread;
	Interpreter* interpreter;
public:
	JVM(cmd* c);
	~JVM();
	void start();
private:
	//�ȼ���sun.misc.VM�࣬����ʼ��
	void initJVM();
	//�������ִ࣬��main����
	void execMain();

	//�����ݸ�main������args��������ת����Java�ַ������飬���������ֲ�������
	Object* createArgsArray();
};

