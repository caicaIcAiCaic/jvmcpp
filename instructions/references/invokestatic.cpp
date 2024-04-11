#include"invokestatic.h"
#include"../base/base_logic.h"
#include"../../rtda/heap/class.h"

void INVOKE_STATIC::fetchOperands(BytecodeReader* reader)
{
	index = index = reader->readUint16();
}

void INVOKE_STATIC::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();	//�õ��˷���������ʱ������
	MethodRefInfo* methodRef = (MethodRefInfo*)rtcp->getConstant(index);	//�õ�������������
	Method* method = methodRef->resolvedMethod();	//����������������,method����Ҫִ�еķ���
	
	Class* c = method->getClass();
	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	if (!method->isStatic())	//��ָ��ֻ��ִ�о�̬����
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, method);
}

