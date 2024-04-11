#pragma once
#include"attributes.h"

//字段表和方法表
class MemberInfo
{
private:
	u2 accessFlags;

	string name;	//nameIndex和descriptorIndex都指向constant_utf8_info数据类型
	string descriptor;

    vector<AttributeInfo*> attributes;
public:
	static vector<MemberInfo*> readMembers(ClassReader& reader, ConstantPool* cp, u2 memberCount);

	MemberInfo(ClassReader& reader, ConstantPool* cp);
	~MemberInfo();

	u2 getAccessFlags();
	string getName();
	string getDescriptor();

	void readAttributes(ClassReader& reader, ConstantPool* cp, u2 count);
	AttributeInfo* getAttribute(string a_name);
};