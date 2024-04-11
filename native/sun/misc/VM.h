#pragma once
#include"../../../rtda/frame.h"

class VM
{
public:
	//private static native void initialize()
	//执行主类的main方法之前必须执行initialize方法
	static void initialize(Frame* frame);
};
