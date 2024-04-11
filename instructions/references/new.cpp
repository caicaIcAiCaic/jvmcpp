#include"new.h"
#include"../../rtda/heap/class.h"
#include"../base/base_logic.h"

void NEW::fetchOperands(BytecodeReader* reader)
{
	index = reader->readUint16();
}

void NEW::execute(Frame* frame)
{
	RunTimeConstantPool* rtcp = frame->method->getClass()->getRunTimeConstantPool();
	ClassRefInfo* classRef = (ClassRefInfo*)rtcp->getConstant(index);
	Class* c = classRef->resolvedClass();

	if (!c->InitStarted())
	{
		frame->resvertNextPC();
		BaseLogic::initClass(frame->thread, c);
		return;
	}

	if (c->isInterface() || c->isAbstract())
	{
		cout << "java.lang.InstantiationError" << endl;
		exit(0);
	}

	Object* ref = c->newObject();
	frame->operandStack.pushRef(ref);
}



