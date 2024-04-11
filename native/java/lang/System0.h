#pragma once
#include"../../../rtda/frame.h"

class System0
{
public:
	static void arraycopy(Frame* frame);
	//private static native void setOut0(PrintStream out)
	//static void setOut0(Frame* frame);
private:
	static bool checkArrayCopy(Object* src, Object* dest);
};

