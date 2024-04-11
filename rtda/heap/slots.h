#pragma once
#include"object.h"
#include"../frame.h"
#include<vector>

//类似与本地变量表，我们也用数组保存类变量与实例变量
class Slots
{
private:
	unsigned int staticSlotCount;
	vector<slot> slots;
public:
	Slots(unsigned int s);
	void setInt(unsigned int index, int val);
	int getInt(unsigned int index);
	void setFloat(unsigned int index, float val);
	float getFloat(unsigned int index);

	void setLong(unsigned int index, long long val);	//64位

	long long getLong(unsigned int index);

	void setDouble(unsigned int index, double val);
	double getDouble(unsigned int index);

	void setRef(unsigned int index, Object* val);

	Object* getRef(unsigned int index);
};




