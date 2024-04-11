#include"classfile.h"
/**
 * Constructor of ClassFile
 * @param reader
 */
ClassFile::ClassFile(ClassReader& reader)   // no member initialization list, don't worry, will assign them later
{
	readAndCheckMagic(reader);
	readAndCheckVersion(reader);

	constantPool = new ConstantPool(reader);

	accessFlags = reader.readU2();
	thisClass = reader.readU2();
	superClass = reader.readU2();

	interfaceCount = reader.readU2();
	interfaces = reader.readU2s(interfaceCount);

	fieldCount = reader.readU2();
	fields = MemberInfo::readMembers(reader, constantPool, fieldCount);

	methodCount = reader.readU2();
	methods = MemberInfo::readMembers(reader, constantPool, methodCount);

	int attributes_count = reader.readU2();
	readAttributes(reader, constantPool,attributes_count);
}

ClassFile::~ClassFile()
{
	for (auto & field : fields) delete field;
	for (auto & method : methods) delete method;
	for (auto & attribute : attributes) delete attribute;
}
/**
 * if magic number != 0xCAFEBABE JVM will exit
 * @param reader
 */
void ClassFile::readAndCheckMagic(ClassReader& reader)
{
	magic = reader.readU4();
	if (magic != (u4)0xCAFEBABE)
	{
		cout << "java.lang.ClassFormatError: magic!" << endl;
		exit(0);
	}
}
void ClassFile::readAndCheckVersion(ClassReader& reader)
{
	this->minorVersion = reader.readU2();
	this->majorVersion = reader.readU2();
	if (majorVersion == 45)
	{
		return;
	}
	else if (majorVersion == 46 || majorVersion == 47 || majorVersion == 48 || majorVersion == 49
		|| majorVersion == 50 || majorVersion == 51 || majorVersion == 52)
	{
		if (minorVersion == 0)
		{
			return;
		}
	}

	cout << "java.lang.UnsupportedClassVersionError!" << endl;	//��֧��JDK8���ϵİ汾
	exit(0);
}
/**
 * read attributes from class file
 * @param reader
 * @param cp
 * @param count
 */
void ClassFile::readAttributes(ClassReader& reader, const ConstantPool* cp, u2 count)
{
	attributes = vector<AttributeInfo*>(count);
	for (u2 i = 0; i < count; i++)
	{
		u2 attr_name_index = reader.readU2();
		u4 attr_length = reader.readU4();

		if (attr_name_index == 0)	//������������Ϊ0��λ�ò�����
		{
			continue;
		}
		string attr_Name = cp->getUtf8(attr_name_index);

		if (attr_Name == "Code")
		{
			attributes[i] = new CodeAttribute(reader, cp, attr_Name, attr_length);
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
		else if (attr_Name == "SourceFile")
		{
			attributes[i] = new SourceFileAttribute(reader,cp ,attr_Name, attr_length);
		}
		else if (attr_Name == "Synthetic")
		{
			attributes[i] = new SyntheticAttribute(attr_Name, attr_length);
		}
		else
		{
			attributes[i] = new UnparsedAttribute(reader, attr_Name,attr_length);
		}
	}	//end--for
}

u2 ClassFile::getMinorVersion()
{
	return minorVersion;
}

u2 ClassFile::getMajorVersion()
{
	return majorVersion;
}
/**
 *
 * @return const the ConstantPool don't allow to modify
 */
const ConstantPool* ClassFile::getConstantPool()
{
	return constantPool;
}

u2 ClassFile::getAccessFlags()
{
	return accessFlags;
}

u2 ClassFile::getThisClass()
{
	return thisClass;
}

u2 ClassFile::getSuperClass()
{
	return superClass;
}

u2 ClassFile::getInterfaceCount()
{
	return interfaceCount;
}

vector<u2>& ClassFile::getInterfaces()
{
	return interfaces;
}

u2 ClassFile::getFieldCount()
{
	return fieldCount;
}

vector<MemberInfo*>& ClassFile::getFields()
{
	return fields;
}

u2 ClassFile::getMethodCount()
{
	return methodCount;
}

vector<MemberInfo*>& ClassFile::getMethods()
{
	return methods;
}
/**
 * ����class�ļ���ָ�����Ƶ�����
 * @param name Ϊʲô��ʹ�����ã���Ϊ������������������ʽ���� const char* != string&
 * @return
 */
AttributeInfo* ClassFile::getAttribute(string name)
{
	for (auto & attribute : attributes)
	{
		if (attribute->getAttributeName() == name) return attribute;
	}
	return nullptr;
}
