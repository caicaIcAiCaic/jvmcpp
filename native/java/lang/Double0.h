#pragma once
#include"../../../rtda/frame.h"

class Double0
{
public:
	//public static native long doubleToRawLongBits(double value)
	static void doubleToRawLongBits(Frame* frame);
	// public static native double longBitsToDouble(long bits);
	static void longBitsToDouble(Frame* frame);
};


