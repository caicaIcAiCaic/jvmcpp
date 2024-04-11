//#define _HAS_STD_BYTE 0
#include "constantpool.h"
#include <Windows.h>

ConstantInfo::ConstantInfo(u1 t):tag(t){}

u1 ConstantInfo::getTag(){return tag;}

ConstantInfo::~ConstantInfo() = default;

ConstantIntegerInfo::ConstantIntegerInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	val = reader.readU4();
}
int ConstantIntegerInfo::getVal()
{
	return val;
}

ConstantFloatInfo::ConstantFloatInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	val = reader.readFloat();
}
float ConstantFloatInfo::getVal()
{
	return val;
}

ConstantLongInfo::ConstantLongInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	val = reader.readLong();
}
long long ConstantLongInfo::getVal()
{
	return val;
}


ConstantDoubleInfo::ConstantDoubleInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	val = reader.readDouble();
}
double ConstantDoubleInfo::getVal()
{
	return val;
}


ConstantUtf8Info::ConstantUtf8Info(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	length = reader.readU2();
	u1* bytearr = new u1[length + 1];
	reader.readBytes(bytearr,length + 1);
	str = decodeMUTF8(bytearr);
}
string& ConstantUtf8Info::getStr()
{
	return str;
}
/**
 * class文件中可能含有中文，单纯的使用字节流构造string会产生乱码，原因时c++采用UTF-8编码，因为字符占1个字节，而中文会占2个或3个字节
 * @param bytearr
 * @return
 */
string ConstantUtf8Info::decodeMUTF8(const u1* bytearr)
{
	wchar_t* chararr = new wchar_t[length + 1]; //生成UTF-16字符数组，UTF16中，不论中文还是英文，都占用2个字节
	wchar_t c, char2, char3;
	int count = 0, chararr_count = 0;

	while (count < length)
	{
		c = (wchar_t)bytearr[count];
		if (c > 127) break; //小于等于127一定是英文，直接赋给UTF16数组即可
		count++;
		chararr[chararr_count++] = c;
	}

	while (count < length)
	{
		c = (wchar_t)bytearr[count];
		switch (c >> 4)
		{
		// 0xxxxxxx
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			count++;
			chararr[chararr_count++] = c;
			break;
		// 110x xxxx    10xx xxxx
		case 12:
		case 13:    //将两字节的UTF8编码转变成UTF16编码
			count += 2;
			if (count > length)
			{
				cout << "malformed input: partial character at end" << endl;
				exit(0);
			}
			char2 = (wchar_t)bytearr[count - 1];
			if ((char2 & 0xC0) != 0x80)
			{
				cout << "malformed input around byte" << count << endl;
				exit(0);
			}
			chararr[chararr_count++] = ((c & 0x1F) << 6) | (char2 & 0x3F);
			break;
		/* 1110 xxxx  10xx xxxx  10xx xxxx*/
		case 14:    //将3字节的UTF8编码转换成2字节的UTF16编码
			count += 3;
			if (count > length)
			{
				cout << "malformed input: partial character at end" << endl;
				exit(0);
			}
			char2 = (wchar_t)bytearr[count - 2];
			char3 = (wchar_t)bytearr[count - 1];
			if ((char2 & 0xC0) != 0x80 || (char3&0xC0) != 0x80)
			{
				cout << "malformed input around byte" << count - 1 << endl;
				exit(0);
			}
			chararr[chararr_count++] = ((c & 0x0F) << 12) | ((char2 & 0x3F) << 6) | (char3 & 0x3F);
			break;
		default:
			cout << "malformed input around byte" << count << endl;
			exit(0);
		}
	}
	// The number of chars produced may be less than utflen
	chararr[chararr_count] = '\0';
	wstring wstr(chararr);
	delete[] chararr;
	return wstring2string(wstr);
}
/**
 * 将wstring转换成string
 * @param wstr
 * @return
 */
string ConstantUtf8Info::wstring2string(const wstring& wstr)
{
	string result;  //函数不能返回局部变量的引用或地址
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

ConstantStringInfo::ConstantStringInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	stringIndex = reader.readU2();
}
u2 ConstantStringInfo::getIndex()
{
	return stringIndex;
}

ConstantClassInfo::ConstantClassInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	nameIndex = reader.readU2();
}

u2 ConstantClassInfo::getNameIndex()
{
	return nameIndex;
}


ConstantNameAndType::ConstantNameAndType(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	nameIndex = reader.readU2();
	descriptorIndex = reader.readU2();
}
u2 ConstantNameAndType::getNameIndex()
{
	return nameIndex;
}
u2 ConstantNameAndType::getDescriptorIndex()
{
	return descriptorIndex;
}

//ConstantFieldInfo、ConstantMethodInfo、ConstantInterfaceMethodInfo
//字段符号引用、方法符号引用、接口方法符号引用的代码相同，故使用ConstantMemberInfo来代替
ConstantMemberrefInfo::ConstantMemberrefInfo(ClassReader& reader, u1 tag) :ConstantInfo(tag)
{
	classIndex = reader.readU2();
	nameAndTypeIndex = reader.readU2();
}
u2 ConstantMemberrefInfo::getClassIndex()
{
	return classIndex;
}
u2 ConstantMemberrefInfo::getNameAndTypeIndex()
{
	return nameAndTypeIndex;
}

ConstantMethodHandleInfo::ConstantMethodHandleInfo(ClassReader& reader, u1 tag):ConstantInfo(tag)
{
	referenceKind = reader.readU1();
	referenceIndex = reader.readU2();
}
ConstantMethodTypeInfo::ConstantMethodTypeInfo(ClassReader& reader, u1 tag) : ConstantInfo(tag)
{
	descriptorIndex = reader.readU2();
}
ConstantInvokeDynamicInfo::ConstantInvokeDynamicInfo(ClassReader& reader, u1 tag) : ConstantInfo(tag)
{
	bootstrapMethodAttrIndex = reader.readU2();
	nameAndTypeIndex = reader.readU2();
}

ConstantPool::ConstantPool(ClassReader& reader)
{
	constant_pool_count = reader.readU2();
	cp = vector<ConstantInfo*>(constant_pool_count);
	cp[0] = nullptr;		//常量池索引从1开始

	for (u2 i = 1; i < constant_pool_count; i++)
	{
		u1 tag = reader.readU1();
		//cout << "i:" << i << "----" << (int)tag << endl;
		switch (tag)
		{
		case 1:cp[i] = new ConstantUtf8Info(reader, tag); break;
		case 3:cp[i] = new ConstantIntegerInfo(reader, tag); break;
		case 4:cp[i] = new ConstantFloatInfo(reader, tag); break;
		case 5:cp[i] = new ConstantLongInfo(reader, tag); i++; break;	//long和double占两个位置
		case 6:cp[i] = new ConstantDoubleInfo(reader, tag); i++; break;
		case 7:cp[i] = new ConstantClassInfo(reader, tag); break;
		case 8:cp[i] = new ConstantStringInfo(reader, tag); break;
		case 9:
		case 10:
		case 11:cp[i] = new ConstantMemberrefInfo(reader, tag); break;
		case 12:cp[i] = new ConstantNameAndType(reader, tag); break;
		case 15:cp[i] = new ConstantMethodHandleInfo(reader, tag); break;
		case 16:cp[i] = new ConstantMethodTypeInfo(reader, tag); break;
		case 18:cp[i] = new ConstantInvokeDynamicInfo(reader, tag); break;
		default:
			cout << "java.lang.ClassFormatError: constant pool tag!" << endl;
			exit(0);
		}
	}
}

ConstantPool::~ConstantPool()
{
	for (u2 i = 1; i < constant_pool_count; i++)
	{
		u1 tag = cp[i]->getTag();
		delete cp[i];

		if (tag == 5 || tag == 6)	//long和double占两个索引位置
			i++;
	}
}

u2 ConstantPool::getConstantPoolCount() const
{
	return constant_pool_count;
}

ConstantInfo* ConstantPool::getConstantInfo(u2 index) const
{
	return cp[index];
}

//注意：以下是按照常量池的索引得出常用的常量池数据类型（共有17种）
void ConstantPool::getNameAndType(string* buf,u2 index) const	//Name、Type
{
	ConstantNameAndType* ntInfo = dynamic_cast<ConstantNameAndType*>(cp[index]);
	buf[0] = getUtf8(ntInfo->getNameIndex());
	buf[1] = getUtf8(ntInfo->getDescriptorIndex());
}
/**
 * 返回该类的父类
 * @param index
 * @return Object没有父类，返回“”
 */
string ConstantPool::getClssName(u2 index) const
{
	if (index == 0) return "";	//没有父类，即Object类
	ConstantClassInfo* cinfo = dynamic_cast<ConstantClassInfo*>(cp[index]);
	return getUtf8(cinfo->getNameIndex());
}
string& ConstantPool::getUtf8(u2 index) const
{
	ConstantUtf8Info* utf8Info = dynamic_cast<ConstantUtf8Info*>(cp[index]);
	//cout << "tag:" << hex << (int)utf8Info->getTag() << endl;
	return utf8Info->getStr();
}