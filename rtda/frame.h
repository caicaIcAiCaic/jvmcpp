#pragma once
#include "..\classfile\memberInfo.h"
#include "heap\class_member.h"
#include "heap\object.h"

//在栈帧中的本地变量表与操作栈中一个slot为4字节
//long与double类型占8字节
struct slot
{
    Object* ref = nullptr;
	unsigned char bytes[4] = { 0 };		//四字节为一个slot
};

//定义本地变量表
class LocalVars
{
private:
	unsigned int maxSize;
	vector<slot> localVarTable;
public:
	explicit LocalVars(unsigned int s);

	void setSlot(unsigned int index, slot s);

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

//栈帧中的操作数栈
class OperandStack
{
private:
	unsigned int maxSize;
	vector<slot> operandStack;
public:
	OperandStack(unsigned int mS);
	void Clear();

	void pushSlot(slot _slot);
	slot popSlot();

	void pushInt(int val);
	int popInt();

	void pushFloat(float val);
	float popFloat();

	void pushLong(long long val);
	long long popLong();

	void pushDouble(double val);
	double popDouble();

	void pushRef(Object* val);
	Object* popRef();

	Object* getRefFromTop(unsigned int n);	//访问从栈顶开始下标为n的slot（栈顶下标为0）
};

class Thread;

class Frame
{
private:
	//记录这个栈帧内的指令地址
	unsigned int nextpc = 0;
public:
	LocalVars localVariablesTable;
	OperandStack operandStack;
	Method* method;	    //指向该栈帧对应的方法（动态链接）
	Thread* thread;
public:
	Frame(Method* m,Thread* t);

	unsigned int getNextPC();
	void setNextPC(unsigned int _pc);

	//在执行new等指令时，可能会初始化类(<clinit>方法)，这时候需要修改nextpc，让他重新指向该指令
	void resvertNextPC();
};