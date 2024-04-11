#pragma once
#include "classreader.h"
#include "constantpool.h"

/**
 * 属性表
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
	u1* bytes;	//释放
public:
	UnparsedAttribute(ClassReader& reader, string& an, u4 al);
	~UnparsedAttribute() override;
};

/**
 * 标志某方法已经不推使用
 */
class DeprecatedAttribute :public AttributeInfo
{
public:
	DeprecatedAttribute(string& an, u4 al);
};

/**
 * 标记此字段或方法不是有Java源码产生的，而是编译器自行添加
 */
class SyntheticAttribute :public AttributeInfo
{
public:
	SyntheticAttribute(string& an, u4 al);
};

/**
 * 记录生成这个class文件的源文件名称，用于生成堆栈信息
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
 * 在字段表中使用，标志由final定义的常量
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
 * 不是code属性中的异常表!
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
 * code属性：Java源码行号与字节码的对应关系
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

	LineNumberTableEntry& getLineNumberTableAt(u2 index);	//返回表中指定索引位置的项
	int getLineNumber(int pc);
};

/**
 * code属性：方法的局部变量描述
 */
struct LocalVariableTableEntry
{
	u2 startPc;
	u2 length;
	string name;	//变量的名称及描述符
	string descriptor;
	u2 index;	//该变量在局部变量表中变量槽的索引位置
};
class LocalVariableTableAttribute :public AttributeInfo
{
private:
    vector<LocalVariableTableEntry> localVariableTable;
public:
	LocalVariableTableAttribute(ClassReader& reader,const ConstantPool* cp ,string& an, u4 al);
	~LocalVariableTableAttribute() override;
	LocalVariableTableEntry& getLocalVariableTableAt(u2 index);	//返回表中指定的项
};

/**
 * code属性中的异常表
 */
struct ExceptionTableEntry
{
public:
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;	//指向运行时常量池索引
};
/**
 * 方法表中，存放字节码指令
 */
class CodeAttribute :public AttributeInfo
{
private:
	u2 maxStack;	//操作数栈与局部变量表的最大长度
	u2 maxLocals;

	u4 code_length;	//字节码长度
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

	AttributeInfo* getAttribute(string name);	//返回指定名称的属性，无此属性则返回NULL
};