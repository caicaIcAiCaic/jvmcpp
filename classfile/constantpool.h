#pragma once
#include "classreader.h"

using std::wstring;
//解析常量池
class ConstantInfo
{
private:
	u1 tag;	//标志该常量池中的一项
public:
	explicit ConstantInfo(u1 t);
    virtual ~ConstantInfo();
	u1 getTag();
};

/**
 * tag为3；后面是高位在前存储的4字节的int值
 */
class ConstantIntegerInfo :public ConstantInfo
{
private:
	int val;
public:
	ConstantIntegerInfo(ClassReader& reader, u1 tag);
	int getVal();
};

/**
 * tag为4；后面是高位在前存储的4字节的float值
 */
class ConstantFloatInfo :public ConstantInfo
{
private:
	float val;
public:
	ConstantFloatInfo(ClassReader& reader, u1 tag);
	float getVal();
};

/**
 * tag为5；后面是高位在前的8字节的long值
 * 8字节占用常量池两个索引位置，即假设当前索引为5，则下一项的的索引从7开始
 */
class ConstantLongInfo :public ConstantInfo
{
private:
	long long val;
public:
	ConstantLongInfo(ClassReader& reader, u1 tag);
	long long getVal();
};

/**
 * tag为6；后面是高位在前的8字节的double值
 * 8字节依旧占两个索引位置
 */
class ConstantDoubleInfo :public ConstantInfo
{
private:
	double val;
public:
	ConstantDoubleInfo(ClassReader& reader, u1 tag);
	double getVal();
};

/**
 * tag为1，后面有两项：2字节的字符串长度length，以及长度为length个子节的字符串
 * 字符串中不能包含null或补充字符，原因是class文件采用MUTF-8方式编码，而C++采用标准的UTF-8
 */
class ConstantUtf8Info :public ConstantInfo
{
private:
	u2 length;
	string str;
public:
	ConstantUtf8Info(ClassReader& reader, u1 tag);
	string& getStr();
private:
	string decodeMUTF8(const u1* bytearr);	//将utf-8转换成UTF-16编码格式
	string wstring2string(const wstring& wstr);
};

/**
 * tag为8；后面是2字节的索引值，它指向CONSTANT_UTF8_INFO类型的一个值
 */
class ConstantStringInfo :public ConstantInfo
{
private:
	u2 stringIndex;
public:
	ConstantStringInfo(ClassReader& reader, u1 tag);
	u2 getIndex();
};

/**
 * tag为7；后面是两字节的索引index，它也指向CONSTANT_UTF8_INFO类型的一个值
 */
class ConstantClassInfo :public ConstantInfo
{
private:
	u2 nameIndex;
public:
	ConstantClassInfo(ClassReader& reader, u1 tag);
	u2 getNameIndex();
};

/**
 * tag为12；它后面有两个值：2字节的索引index1，指向CONSTANT_UTF8_INFO类型字段或方法的名称
 * 2字节的索引index2，指向CONSTANT_UTF8_INFO类型字段或方法的描述符（字段的类型、方法的参数列表类型与返回值类型）
 */
class ConstantNameAndType :public ConstantInfo
{
private:
	u2 nameIndex;
	u2 descriptorIndex;
public:
	ConstantNameAndType(ClassReader& reader, u1 tag);
	u2 getNameIndex();
	u2 getDescriptorIndex();
};

/**
 * tag为9、10、11，表示字段、方法、接口方法；三者的表现形式一样
 * 后面有两个值，都是2字节，分别指向CONSTANT_CLASS_INFO与CONSTANT_NameAndType_INFO
 */
class ConstantMemberrefInfo :public ConstantInfo
{
private:
	u2 classIndex;
	u2 nameAndTypeIndex;
public:
	ConstantMemberrefInfo(ClassReader& reader, u1 tag);
	u2 getClassIndex();
	u2 getNameAndTypeIndex();
};

/**
 * tag为15
 */
class ConstantMethodHandleInfo :public ConstantInfo
{
private:
	u1 referenceKind;
	u2 referenceIndex;
public:
	ConstantMethodHandleInfo(ClassReader& reader, u1 tag);
};

/**
 * 16
 */
class ConstantMethodTypeInfo :public ConstantInfo
{
private:
	u2 descriptorIndex;
public:
	ConstantMethodTypeInfo(ClassReader& reader, u1 tag);
};

/**
 * 18
 */
class ConstantInvokeDynamicInfo :public ConstantInfo
{
private:
	u2 bootstrapMethodAttrIndex;
	u2 nameAndTypeIndex;
public:
	ConstantInvokeDynamicInfo(ClassReader& reader, u1 tag);
};

/**
 * 常量池：实际上就是一个数组
 */
class ConstantPool
{
private:
	u2 constant_pool_count;
	vector<ConstantInfo*> cp;	//释放内存
public:
	explicit ConstantPool(ClassReader& reader);
	~ConstantPool();

	u2 getConstantPoolCount() const;
	ConstantInfo* getConstantInfo(u2 index) const;	//得到指定索引位置的项

	//一般用于字段、方法、接口方法（即ConstantMemberInfo）的第二个值
	//它得到两个string类型，分别表示其名称和描述符
	void getNameAndType(string* buf,u2 index) const;	

	//一般用于ConsatntMemberInfo的第一个值
	//它得到类名
	string getClssName(u2 index) const;

	string& getUtf8(u2 index) const;
};