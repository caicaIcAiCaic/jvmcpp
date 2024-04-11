#pragma once
#include "classreader.h"
#include "constantpool.h"

/**
 * ���Ա�
 */
class AttributeInfo
{
private:
	string attrName;
	u4 attrLen;
public:
	AttributeInfo(string& an, u4 al);
    virtual ~AttributeInfo();
	string getAttributeName();
	u2 getAttributeLength();
};

/**
 * Attribute Unparsed
 */
class UnparsedAttribute :public AttributeInfo
{
private:
	u1* bytes;	//�ͷ�
public:
	UnparsedAttribute(ClassReader& reader, string& an, u4 al);
	~UnparsedAttribute() override;
};

/**
 * ��־ĳ�����Ѿ�����ʹ��
 */
class DeprecatedAttribute :public AttributeInfo
{
public:
	DeprecatedAttribute(string& an, u4 al);
};

/**
 * ��Ǵ��ֶλ򷽷�������JavaԴ������ģ����Ǳ������������
 */
class SyntheticAttribute :public AttributeInfo
{
public:
	SyntheticAttribute(string& an, u4 al);
};

/**
 * ��¼�������class�ļ���Դ�ļ����ƣ��������ɶ�ջ��Ϣ
 */
class SourceFileAttribute :public AttributeInfo
{
private:
	string sourceFile;
public:
	SourceFileAttribute(ClassReader& reader,const ConstantPool* cp, string& an, u4 al);
	string getSourceFile();
};

/**
 * ���ֶα���ʹ�ã���־��final����ĳ���
 */
class ConstantValueAttribute : public AttributeInfo
{
private:
	u2 constantValueIndex;
public:
	ConstantValueAttribute(ClassReader& reader, string& an, u4 al);
	u2 getConstantValueIndex();
};

/**
 * ����code�����е��쳣��!
 */
class ExceptionsAttribute :public AttributeInfo
{
private:
	u2 exceptions_length;
	vector<u2> exceptionIndexTable;	
public:
	ExceptionsAttribute(ClassReader& reader, string& an, u4 al);
	u2 getExceptionLength();
	vector<u2>& getExceptionIndexTable();
};

/**
 * code���ԣ�JavaԴ���к����ֽ���Ķ�Ӧ��ϵ
 */
struct LineNumberTableEntry
{
    u2 startPc;
    u2 lineNumber;
};
class LineNumberTableAttribute :public AttributeInfo
{
private:
    vector<LineNumberTableEntry> lineNumberTable;
public:
	LineNumberTableAttribute(ClassReader& reader, string& an, u4 al);
	~LineNumberTableAttribute() override;

	LineNumberTableEntry& getLineNumberTableAt(u2 index);	//���ر���ָ������λ�õ���
	int getLineNumber(int pc);
};

/**
 * code���ԣ������ľֲ���������
 */
struct LocalVariableTableEntry
{
	u2 startPc;
	u2 length;
	string name;	//���������Ƽ�������
	string descriptor;
	u2 index;	//�ñ����ھֲ��������б����۵�����λ��
};
class LocalVariableTableAttribute :public AttributeInfo
{
private:
    vector<LocalVariableTableEntry> localVariableTable;
public:
	LocalVariableTableAttribute(ClassReader& reader,const ConstantPool* cp ,string& an, u4 al);
	~LocalVariableTableAttribute() override;
	LocalVariableTableEntry& getLocalVariableTableAt(u2 index);	//���ر���ָ������
};

/**
 * code�����е��쳣��
 */
struct ExceptionTableEntry
{
public:
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;	//ָ������ʱ����������
};
/**
 * �������У�����ֽ���ָ��
 */
class CodeAttribute :public AttributeInfo
{
private:
	u2 maxStack;	//������ջ��ֲ����������󳤶�
	u2 maxLocals;

	u4 code_length;	//�ֽ��볤��
	u1* code;

    vector<ExceptionTableEntry> exceptionTable;
    vector<AttributeInfo*> attributes;
public:
	CodeAttribute(ClassReader& reader, const ConstantPool* cp, string an, u4 al);
	~CodeAttribute() override;

	u2 getMaxStack();
	u2 getMaxLocals();

	u4 getCodeLength();
	u1* getCode();

	vector<ExceptionTableEntry>& getExceptionTable();

	AttributeInfo* getAttribute(string name);	//����ָ�����Ƶ����ԣ��޴������򷵻�NULL
};