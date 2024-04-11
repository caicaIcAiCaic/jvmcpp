#pragma once
#include"class_member.h"

class RunTimeConstantPool;
//该类型可以看作运行时常量池，它存放所有的整型常量、浮点型常量、字符串字面量；
//以及类、字段、方法、接口方法的符号引用

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
	RunTimeConstantPool* rtcp;	//指向运行时常量池
	string className;
	Class* _class;  //缓存指向解析后的直接引用
public:
	SymRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c);

	Class* resolvedClass();	//如果类符号引用已经解析，直接返回类指针，否则调用resolveClassRef进行解析
	//Java虚拟机规范给出了类符号引用的解析步骤：
	//				假设D类通过符号引用N引用了类C，则先用D的类加载器加载C，然后检查D是否有访问C的权限
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
	string name;    //字段、方法名
	string descriptor;  //描述符
public:
	MemberRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d);
};

class FieldRefInfo :public MemberRefInfo
{
public:
	Field* field;	//field字段缓存解析后的字段指针
public:
	FieldRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Field* f);

	Field* resolvedField();	//字段符号引用解析
private:
	void resolveFieldRef();
	Field* lookupField(Class* c, string name, string descriptor);	//查找类C中是否有字段name
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
	//在类C及其父类中寻找指定的方法
	static Method* lookupMethodInClass(Class* c, string name, string descriptor);
	//在接口及其父接口中寻找指定的方法
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

//运行时常量池主要存放字面量和符号引用
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