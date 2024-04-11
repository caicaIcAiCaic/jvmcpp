#pragma once
#include"class_member.h"

class RunTimeConstantPool;
//�����Ϳ��Կ�������ʱ�����أ���������е����ͳ����������ͳ������ַ�����������
//�Լ��ࡢ�ֶΡ��������ӿڷ����ķ�������

class Constant
{
public:
	int tag;
public:
	Constant(int t);
};

class IntInfo :public Constant	//3
{
public:
	int value;
public:
	IntInfo(int t, int v);
};

class FloatInfo :public Constant	//4
{
public:
	float value;
public:
	FloatInfo(int t, float v);
};

class LongInfo :public Constant	//5
{
public:
	long long value;
public:
	LongInfo(int t, long long v);
};

class DoubleInfo :public Constant	//6
{
public:
	double value;
public:
	DoubleInfo(int t, double v);
};

class StringInfo :public Constant	//8
{
public:
	string value;
public:
	StringInfo(int t, string v);
};

class SymRefInfo :public Constant
{
public:
	RunTimeConstantPool* rtcp;	//ָ������ʱ������
	string className;
	Class* _class;  //����ָ��������ֱ������
public:
	SymRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c);

	Class* resolvedClass();	//�������������Ѿ�������ֱ�ӷ�����ָ�룬�������resolveClassRef���н���
	//Java������淶��������������õĽ������裺
	//				����D��ͨ����������N��������C��������D�������������C��Ȼ����D�Ƿ��з���C��Ȩ��
private:
	void resolveClassRef();
};

class ClassRefInfo :public SymRefInfo
{
public:
	ClassRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c);
};

class MemberRefInfo :public SymRefInfo
{
public:
	string name;    //�ֶΡ�������
	string descriptor;  //������
public:
	MemberRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d);
};

class FieldRefInfo :public MemberRefInfo
{
public:
	Field* field;	//field�ֶλ����������ֶ�ָ��
public:
	FieldRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Field* f);

	Field* resolvedField();	//�ֶη������ý���
private:
	void resolveFieldRef();
	Field* lookupField(Class* c, string name, string descriptor);	//������C���Ƿ����ֶ�name
};

class MethodRefInfo :public MemberRefInfo
{
public:
	Method* method;
public:
	MethodRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Method* m);

	Method* resolvedMethod();
private:
	void resolveMethodRef();
	Method* lookupMethod(Class* c, string name, string descriptor);
public:
	//����C���丸����Ѱ��ָ���ķ���
	static Method* lookupMethodInClass(Class* c, string name, string descriptor);
	//�ڽӿڼ��丸�ӿ���Ѱ��ָ���ķ���
	static Method* lookupMethodInInterfaces(vector<Class*>ifaces, string name, string descriptor);

};

class InterfaceMethodRefInfo :public MemberRefInfo
{
public:
	Method* method;
public:
	InterfaceMethodRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Method* m);
	Method* resolvedInterfaceMethod();
private:
	void resolveInterfaceMethodRef();
	Method* lookupInterfaceMethod(Class* iface, string name, string descriptor);
};

//����ʱ��������Ҫ����������ͷ�������
class RunTimeConstantPool
{
private:
	Class* _class;
	unsigned int constant_pool_count;
	vector<Constant*> consts;
public:
	RunTimeConstantPool(Class* c, const ConstantPool* cp);
	~RunTimeConstantPool();

	Class* getClass();
	Constant* getConstant(unsigned int index);
};