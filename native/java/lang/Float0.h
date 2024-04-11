#pragma once
#include"../../../rtda/frame.h"

class Float0
{
public:
	//public static native int floatToRawIntBits(float value)
	static void floatToRawIntBits(Frame* frame);
	// public static native float intBitsToFloat(int bits);
	static void intBitsToFloat(Frame* frame);
};

