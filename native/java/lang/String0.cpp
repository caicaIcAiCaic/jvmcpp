#include"String0.h"
#include"../../../rtda/heap/string_pool.h"

void String0::intern(Frame* frame)
{
	Object* t = frame->localVariablesTable.getRef(0);
	Object* interned = StringPool::internString(t);
	frame->operandStack.pushRef(interned);
}

