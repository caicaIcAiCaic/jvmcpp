#include"registry.h"
#include"java/lang/Class0.h"
#include"java/lang/Object0.h"
#include"java/lang/System0.h"
#include"java/lang/Float0.h"
#include"java/lang/Double0.h"
#include"java/lang/String0.h"
#include"sun/misc/VM.h"
#include"java/lang/Throwable0.h"

void emptyNativeMethod(Frame* frame)
{

}

unordered_map<string, PF> REGISTRY::registry = unordered_map<string, PF>();

void REGISTRY::init()
{
	Register("java/lang/Object", "getClass", "()Ljava/lang/Class;", Object0::getClass);
	Register("java/lang/Object", "hashCode", "()I", Object0::hashCode);
	Register("java/lang/Object", "clone", "()Ljava/lang/Object;", Object0::clone);

	Register("java/lang/Class", "getPrimitiveClass",
		"(Ljava/lang/String;)Ljava/lang/Class;", Class0::getPrimitiveClass);
	Register("java/lang/Class", "getName0",
		"()Ljava/lang/String;", Class0::getName0);
	Register("java/lang/Class", "desiredAssertionStatus0",
		"(Ljava/lang/Class;)Z", Class0::desiredAssertionStatus0);
	
	Register("java/lang/System", "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", System0::arraycopy);

	Register("java/lang/Float", "floatToRawIntBits", "(F)I", Float0::floatToRawIntBits);
	Register("java/lang/Float", "intBitsToFloat", "(I)F", Float0::intBitsToFloat);
	Register("java/lang/Double", "doubleToRawLongBits", "(D)J", Double0::doubleToRawLongBits);
	Register("java/lang/Double", "longBitsToDouble", "(J)D", Double0::longBitsToDouble);

	Register("java/lang/String", "intern", "()Ljava/lang/String;", String0::intern);

	Register("sun/misc/VM", "initialize", "()V", VM::initialize);

	Register("java/lang/Throwable", "fillInStackTrace", "(I)Ljava/lang/Throwable;", Throwable0::fillInStackTrace);
}

void REGISTRY::Register(string className, string methodName, string methodDescriptor, PF method)
{
	string key = className + "~" + methodName + "~" + methodDescriptor;
	registry.insert({ key,method });
}

PF REGISTRY::FindNativeMethod(string className, string methodName, string methodDescriptor)
{
	string key = className + "~" + methodName + "~" + methodDescriptor;
	if (registry.find(key) != registry.end()) return registry.find(key)->second;
	if (methodDescriptor == "()V" && methodName == "registerNatives") return emptyNativeMethod;
	return nullptr;
}

