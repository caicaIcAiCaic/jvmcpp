#pragma once
#include"memberInfo.h"

using std::cout;
using std::endl;

//该目录下要实现一个简易的javap工具，JDK本身提供了一个功能强大的命令行工具javap
//它可以反编译class文件，得出该类的具体信息

//类文件结构
//旨在用于生成Class结构体，一旦Class运行时数据结构在方法区生成，该对象就没用了
class ClassFile
{
private:
	u4 magic;
	u2 minorVersion;
	u2 majorVersion;

	ConstantPool* constantPool;	//受限于C++类成员的构造顺序，对象成员一定比普通成员优先构造，这里只能使用指针

	u2 accessFlags;

	u2 thisClass;	//它指向一个constant_class_info的数据类型
	u2 superClass;
	u2 interfaceCount;
	vector<u2> interfaces;

	u2 fieldCount;
	vector<MemberInfo*> fields;		//释放空间
	u2 methodCount;
	vector<MemberInfo*> methods;	//释放

//	u2 attributes_count;
    vector<AttributeInfo*> attributes;
//	AttributeInfo** attributes;	//class文件的属性

public:
	explicit ClassFile(ClassReader& reader);
	~ClassFile();

	u2 getMinorVersion();
	u2 getMajorVersion();

	const ConstantPool* getConstantPool();

	u2 getAccessFlags();

	u2 getThisClass();
	u2 getSuperClass();

	u2 getInterfaceCount();
    vector<u2>& getInterfaces();

	u2 getFieldCount();
	vector<MemberInfo*>& getFields();

	u2 getMethodCount();
	vector<MemberInfo*>& getMethods();

	void readAttributes(ClassReader& reader,const ConstantPool* cp,u2 count);
	AttributeInfo* getAttribute(string name);	//返回class文件中指定名称的属性，无此属性则返回NULL

private:
    void readAndCheckMagic(ClassReader& reader);
    void readAndCheckVersion(ClassReader& reader);
};