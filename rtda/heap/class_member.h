#pragma once
#include "../../classfile/classfile.h"
#include "access_flags.h"
#include "method_descriptor.h"

class Class;
//字段与方法都属于类的成员，它们有一些相同的信息：
//访问标志、名字、描述符
//析构函数
class ClassMember
{
private:
	unsigned short accessFlag;
	string name;
	string descriptor;
	Class* _class;	//存放class结构体指针
public:
	ClassMember(MemberInfo* memberinfo,Class* c);	//从class文件中复制数据

	bool isStatic();
	bool isPublic();
	bool isProtected();
	bool isPrivate();
	bool isLongOrDouble();
	bool isFinal();
	bool isAccessibleTo(Class* d);
	bool isAbstract();
	bool isNative();

	string getName();
	string getDescriptor();
	Class* getClass();
};

//字段、存储在Class类中，可以通过Class类访问其字段信息
//析构函数
class Field :public ClassMember
{
private:
	unsigned int slotId;	//标志该字段在字段数组Slots中的索引;用于存储和读取数据
	unsigned int constValueIndex = 0;	//如果这个字段为final static，标志它的值在常量池的索引
public:
	Field(MemberInfo* memberinfo, Class* c);
	static vector<Field*> newFields(ClassFile* cf, Class* c);

	void setSlotId(unsigned int s);
	unsigned int getSlotId();
	unsigned int getConstValueIndex();
};

class ClassRefInfo;

struct ExceptionHandler
{
	int startPC;
	int endPC;
	int handlerPC;
	ClassRefInfo* catchType;
};

//方法字段稍微复杂一些，因为方法中有字节码
class Method :public ClassMember
{
private:
	u2 maxStack;//操作数栈最大深度
	u2 maxLocals;//局部变量表最大槽数

	u4 code_length = 0;//字节码长度
	u1* byteCode = nullptr;	//字节码

	u4 argSlotCount;

	vector<ExceptionHandler> exceptionTable;	//异常表；也是从classfile中code属性中得到
	LineNumberTableAttribute* lineNumberTable;	//Java class文件中的字节码与源代码的对应关系
public:
	static vector<Method*> newMethods(ClassFile* cf, Class* c);
	Method(MemberInfo* memberinfo, Class* c);

	void calcArgSlotCount(vector<string> parameterTypes);

	int findExceptionHandler(Class* exClass, int pc);
	int getLineNumber(int pc);	//根据字节码的行号返回源文件的行号
private:
	//本地方法在字节码中没有code属性，所以要手动给code属性赋值
	void injectCodeAttribute(string returnType);	//为本地方法注入字节码和其他信息
	MethodDescriptor parseMethodDescriptor(string descriptor);

public:
	u2 getMaxStack();
	u2 getMaxLocals();

	u4 getCodeLength();
	u1* getCode();

	u4 getArgSlotCount();
};



