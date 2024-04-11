#pragma once
#include"attributes.h"

//�ֶα�ͷ�����
class MemberInfo
{
private:
	u2 accessFlags;

	string name;	//nameIndex��descriptorIndex��ָ��constant_utf8_info��������
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