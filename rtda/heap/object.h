#pragma once
#include<string>

using std::string;

class Class;
class Slots;

class Object
{
private:
	Class* _class;		//ָ��Class��
	void* extra;	    //���ö���ʵ����java/lang/Class���ʵ��ʱ��extraָ���Ӧ��Class�ṹ��
	
	unsigned int arraylength;   //���鳤��
	void* data;		    //���ʵ���ֶ�

public:
	Object(Class* c,void* s,unsigned int al = 0);	//�´����Ķ���Ӧ�ø��ó�ʼֵ
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

	//����Object��ָ��ʵ���ֶθ�ֵ
	void SetRefVar(string name, string descriptor, Object* ref);
	Object* GetRefVar(string name, string descriptor);	//�õ��ö����е�ָ���ʵ���ֶ�

	bool IsInstanceOf(Class* c);
	Object* Clone();
	static void ArrayCopy(Object* src, Object* dst, int srcPos, int dstPos, int length);

};
