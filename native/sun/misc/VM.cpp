#include "VM.h"
#include"../../../instructions/base/base_logic.h"
#include"../../../rtda/heap/string_pool.h"

void VM::initialize(Frame* frame)
{
	Class* vmClass = frame->method->getClass();
	Object* savedProps = vmClass->getRefVar("savedProps", "Ljava/util/Properties;");
	Object* key = StringPool::JString(vmClass->getClassLoader(), "foo");
	Object* val = StringPool::JString(vmClass->getClassLoader(), "bar");

	frame->operandStack.pushRef(savedProps);
	frame->operandStack.pushRef(key);
	frame->operandStack.pushRef(val);

	Class* propsClass = vmClass->getClassLoader()->loadClass("java/util/Properties");
	Method* setPropMethod = propsClass->getInstanceMethod("setProperty",
		"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
	BaseLogic::invokeMethod(frame, setPropMethod);
}
