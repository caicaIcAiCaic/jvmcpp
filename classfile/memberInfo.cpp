#include"memberInfo.h"

vector<MemberInfo*> MemberInfo::readMembers(ClassReader& reader, ConstantPool* cp, u2 memberCount)
{
	vector<MemberInfo*> members(memberCount);
	for (u2 i = 0; i < memberCount; i++)
	{
		members[i] = new MemberInfo(reader, cp);
	}
	return members;
}

MemberInfo::MemberInfo(ClassReader& reader, ConstantPool* cp)
{
	accessFlags = reader.readU2();

	name =cp->getUtf8(reader.readU2());
	descriptor = cp->getUtf8(reader.readU2());

	int attributes_count = reader.readU2();
	readAttributes(reader, cp,attributes_count);
}

MemberInfo::~MemberInfo()
{
	for (auto & attribute : attributes)
	{
		delete attribute;
	}
}

u2 MemberInfo::getAccessFlags()
{
	return accessFlags;
}

string MemberInfo::getName()
{
	return name;
}

string MemberInfo::getDescriptor()
{
	return descriptor;
}

void MemberInfo::readAttributes(ClassReader& reader, ConstantPool* cp, u2 count)
{
	attributes = vector<AttributeInfo*>(count);
	for (int i = 0; i < count; i++)
	{
		u2 attr_name_index = reader.readU2();
		u4 attr_length = reader.readU4();

		if (attr_name_index == 0)	//常量池中索引为0的位置不可用
			continue;

		string attr_Name = cp->getUtf8(attr_name_index);

		if (attr_Name == "Code")
		{
            attributes[i] = new CodeAttribute(reader,cp,attr_Name,attr_length);
		}
		else if (attr_Name == "ConstantValue")
		{
			attributes[i] = new ConstantValueAttribute(reader, attr_Name, attr_length);
		}
		else if (attr_Name == "Deprecated")
		{
			attributes[i] = new DeprecatedAttribute(attr_Name, attr_length);
		}
		else if (attr_Name == "Exceptions")
		{
			attributes[i] = new ExceptionsAttribute(reader, attr_Name, attr_length);
		}
		else if (attr_Name == "Synthetic")
		{
			attributes[i] = new SyntheticAttribute(attr_Name, attr_length);
		}
		else
		{
			attributes[i] = new UnparsedAttribute(reader, attr_Name, attr_length);
		}
	}	//end--for
}
/**
 * 返回方法或字段的指定属性
 * @param name
 * @return 如果不存在这个属性，则返回nullptr
 */
AttributeInfo* MemberInfo::getAttribute(string a_name)
{
	for (auto & attribute : attributes)
	{
		if (attribute->getAttributeName() == a_name) return attribute;
	}
	return nullptr;
}