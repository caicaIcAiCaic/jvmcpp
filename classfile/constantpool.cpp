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
 * class�ļ��п��ܺ������ģ�������ʹ���ֽ�������string��������룬ԭ��ʱc++����UTF-8���룬��Ϊ�ַ�ռ1���ֽڣ������Ļ�ռ2����3���ֽ�
 * @param bytearr
 * @return
 */
string ConstantUtf8Info::decodeMUTF8(const u1* bytearr)
{
	wchar_t* chararr = new wchar_t[length + 1]; //����UTF-16�ַ����飬UTF16�У��������Ļ���Ӣ�ģ���ռ��2���ֽ�
	wchar_t c, char2, char3;
	int count = 0, chararr_count = 0;

	while (count < length)
	{
		c = (wchar_t)bytearr[count];
		if (c > 127) break; //С�ڵ���127һ����Ӣ�ģ�ֱ�Ӹ���UTF16���鼴��
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
		case 13:    //�����ֽڵ�UTF8����ת���UTF16����
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
		case 14:    //��3�ֽڵ�UTF8����ת����2�ֽڵ�UTF16����
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
 * ��wstringת����string
 * @param wstr
 * @return
 */
string ConstantUtf8Info::wstring2string(const wstring& wstr)
{
	string result;  //�������ܷ��ؾֲ����������û��ַ
	//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ  
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

//ConstantFieldInfo��ConstantMethodInfo��ConstantInterfaceMethodInfo
//�ֶη������á������������á��ӿڷ����������õĴ�����ͬ����ʹ��ConstantMemberInfo������
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
	cp[0] = nullptr;		//������������1��ʼ

	for (u2 i = 1; i < constant_pool_count; i++)
	{
		u1 tag = reader.readU1();
		//cout << "i:" << i << "----" << (int)tag << endl;
		switch (tag)
		{
		case 1:cp[i] = new ConstantUtf8Info(reader, tag); break;
		case 3:cp[i] = new ConstantIntegerInfo(reader, tag); break;
		case 4:cp[i] = new ConstantFloatInfo(reader, tag); break;
		case 5:cp[i] = new ConstantLongInfo(reader, tag); i++; break;	//long��doubleռ����λ��
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

		if (tag == 5 || tag == 6)	//long��doubleռ��������λ��
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

//ע�⣺�����ǰ��ճ����ص������ó����õĳ������������ͣ�����17�֣�
void ConstantPool::getNameAndType(string* buf,u2 index) const	//Name��Type
{
	ConstantNameAndType* ntInfo = dynamic_cast<ConstantNameAndType*>(cp[index]);
	buf[0] = getUtf8(ntInfo->getNameIndex());
	buf[1] = getUtf8(ntInfo->getDescriptorIndex());
}
/**
 * ���ظ���ĸ���
 * @param index
 * @return Objectû�и��࣬���ء���
 */
string ConstantPool::getClssName(u2 index) const
{
	if (index == 0) return "";	//û�и��࣬��Object��
	ConstantClassInfo* cinfo = dynamic_cast<ConstantClassInfo*>(cp[index]);
	return getUtf8(cinfo->getNameIndex());
}
string& ConstantPool::getUtf8(u2 index) const
{
	ConstantUtf8Info* utf8Info = dynamic_cast<ConstantUtf8Info*>(cp[index]);
	//cout << "tag:" << hex << (int)utf8Info->getTag() << endl;
	return utf8Info->getStr();
}