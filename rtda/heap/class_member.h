#pragma once
#include "../../classfile/classfile.h"
#include "access_flags.h"
#include "method_descriptor.h"

class Class;
//�ֶ��뷽����������ĳ�Ա��������һЩ��ͬ����Ϣ��
//���ʱ�־�����֡�������
//��������
class ClassMember
{
private:
	unsigned short accessFlag;
	string name;
	string descriptor;
	Class* _class;	//���class�ṹ��ָ��
public:
	ClassMember(MemberInfo* memberinfo,Class* c);	//��class�ļ��и�������

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

//�ֶΡ��洢��Class���У�����ͨ��Class��������ֶ���Ϣ
//��������
class Field :public ClassMember
{
private:
	unsigned int slotId;	//��־���ֶ����ֶ�����Slots�е�����;���ڴ洢�Ͷ�ȡ����
	unsigned int constValueIndex = 0;	//�������ֶ�Ϊfinal static����־����ֵ�ڳ����ص�����
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

//�����ֶ���΢����һЩ����Ϊ���������ֽ���
class Method :public ClassMember
{
private:
	u2 maxStack;//������ջ������
	u2 maxLocals;//�ֲ�������������

	u4 code_length = 0;//�ֽ��볤��
	u1* byteCode = nullptr;	//�ֽ���

	u4 argSlotCount;

	vector<ExceptionHandler> exceptionTable;	//�쳣��Ҳ�Ǵ�classfile��code�����еõ�
	LineNumberTableAttribute* lineNumberTable;	//Java class�ļ��е��ֽ�����Դ����Ķ�Ӧ��ϵ
public:
	static vector<Method*> newMethods(ClassFile* cf, Class* c);
	Method(MemberInfo* memberinfo, Class* c);

	void calcArgSlotCount(vector<string> parameterTypes);

	int findExceptionHandler(Class* exClass, int pc);
	int getLineNumber(int pc);	//�����ֽ�����кŷ���Դ�ļ����к�
private:
	//���ط������ֽ�����û��code���ԣ�����Ҫ�ֶ���code���Ը�ֵ
	void injectCodeAttribute(string returnType);	//Ϊ���ط���ע���ֽ����������Ϣ
	MethodDescriptor parseMethodDescriptor(string descriptor);

public:
	u2 getMaxStack();
	u2 getMaxLocals();

	u4 getCodeLength();
	u1* getCode();

	u4 getArgSlotCount();
};



