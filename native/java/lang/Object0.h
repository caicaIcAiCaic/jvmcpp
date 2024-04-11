#pragma once
#include"../../../rtda/frame.h"

class Object0
{
public:
	//public final native Class<?> getClass();
	static void getClass(Frame* frame);

	//public native int hashCode()
	static void hashCode(Frame* frame);

	//protected native Object clone()
	static void clone(Frame* frame);
};
