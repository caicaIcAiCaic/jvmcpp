#pragma once
#include"../../../rtda/frame.h"

class Class0
{
public:
	//static native Class<?> getPrimitiveClass(string name)
	static void getPrimitiveClass(Frame* frame);

	//private native String getName0()
	static void getName0(Frame* frame);

	//private static native boolean desiredAssertionStatus0(Class<?> clazz)
	static void desiredAssertionStatus0(Frame* frame);
};