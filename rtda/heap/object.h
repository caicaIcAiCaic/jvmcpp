#pragma once
#include<string>

using std::string;

class Class;
class Slots;

class Object
{
private:
	Class* _class;		//指向Class类
	void* extra;	    //当该对象实例是java/lang/Class类的实例时，extra指向对应的Class结构体
	
	unsigned int arraylength;   //数组长度
	void* data;		    //存放实例字段

public:
	Object(Class* c,void* s,unsigned int al = 0);	//新创建的对象应该赋好初始值
//	~Object();

	Class* getClass();
	void* getExtra();
	void setExtra(void* e);

	Slots* getFields();
	char* getBytes();			//b 8
	short* getShorts();			//s 16
	int* getInts();				//i 32
	long long* getLongs();		//l 64
	wchar_t* getChars();	//c 16
	float* getFloats();			//f 32
	double* getDoubles();		//d 64
	Object** getObjects();		//r 

	unsigned int getArrayLength();

	//给该Object中指定实例字段赋值
	void SetRefVar(string name, string descriptor, Object* ref);
	Object* GetRefVar(string name, string descriptor);	//得到该对象中的指令的实例字段

	bool IsInstanceOf(Class* c);
	Object* Clone();
	static void ArrayCopy(Object* src, Object* dst, int srcPos, int dstPos, int length);

};
