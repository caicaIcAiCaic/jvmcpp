#pragma once
#include "..\classfile\memberInfo.h"
#include "heap\class_member.h"
#include "heap\object.h"

//��ջ֡�еı��ر����������ջ��һ��slotΪ4�ֽ�
//long��double����ռ8�ֽ�
struct slot
{
    Object* ref = nullptr;
	unsigned char bytes[4] = { 0 };		//���ֽ�Ϊһ��slot
};

//���屾�ر�����
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

	void setLong(unsigned int index, long long val);	//64λ
	long long getLong(unsigned int index);

	void setDouble(unsigned int index, double val);
	double getDouble(unsigned int index);

	void setRef(unsigned int index, Object* val);
	Object* getRef(unsigned int index);
};

//ջ֡�еĲ�����ջ
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

	Object* getRefFromTop(unsigned int n);	//���ʴ�ջ����ʼ�±�Ϊn��slot��ջ���±�Ϊ0��
};

class Thread;

class Frame
{
private:
	//��¼���ջ֡�ڵ�ָ���ַ
	unsigned int nextpc = 0;
public:
	LocalVars localVariablesTable;
	OperandStack operandStack;
	Method* method;	    //ָ���ջ֡��Ӧ�ķ�������̬���ӣ�
	Thread* thread;
public:
	Frame(Method* m,Thread* t);

	unsigned int getNextPC();
	void setNextPC(unsigned int _pc);

	//��ִ��new��ָ��ʱ�����ܻ��ʼ����(<clinit>����)����ʱ����Ҫ�޸�nextpc����������ָ���ָ��
	void resvertNextPC();
};