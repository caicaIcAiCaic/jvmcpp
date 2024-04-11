#include"invokestatic.h"
#include"../base/base_logic.h"
#include"../../rtda/heap/class.h"

void INVOKE_STATIC::fetchOperands(BytecodeReader* reader)
{
	index = index = reader->readUint16();
}

void INVOKE_STATIC::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();	//得到此方法的运行时常量池
	MethodRefInfo* methodRef = (MethodRefInfo*)rtcp->getConstant(index);	//得到方法符号引用
	Method* method = methodRef->resolvedMethod();	//解析方法符号引用,method就是要执行的方法
	
	Class* c = method->getClass();
	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	if (!method->isStatic())	//该指令只能执行静态方法
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	BaseLogic::invokeMethod(frame, method);
}

