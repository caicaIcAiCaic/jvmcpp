#pragma once
#include"object.h"
#include"../frame.h"
#include<vector>

//�����뱾�ر���������Ҳ�����鱣���������ʵ������
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

	void setLong(unsigned int index, long long val);	//64λ

	long long getLong(unsigned int index);

	void setDouble(unsigned int index, double val);
	double getDouble(unsigned int index);

	void setRef(unsigned int index, Object* val);

	Object* getRef(unsigned int index);
};




