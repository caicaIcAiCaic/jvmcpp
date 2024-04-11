#include"invokenative.h"
#include"../../rtda/heap/class.h"
#include"../../native/registry.h"

void INVOKE_NATIVE::fetchOperands(BytecodeReader* reader)
{

}

void INVOKE_NATIVE::execute(Frame* frame)
{
	Method* method = frame->method;
	string className = method->getClass()->getName();
	string methodName = method->getName();
	string methodDescriptor = method->getDescriptor();

	PF nativeMethod = REGISTRY::FindNativeMethod(className, methodName, methodDescriptor);
	if (nativeMethod == nullptr)
	{
		string methodInfo = className + "." + methodName + methodDescriptor;
		cout << "java.lang.UnsatisfiedLinkError: " << methodInfo << endl;
		exit(0);
	}
	nativeMethod(frame);
}

