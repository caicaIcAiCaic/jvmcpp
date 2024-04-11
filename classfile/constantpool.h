#pragma once
#include "classreader.h"

using std::wstring;
//����������
class ConstantInfo
{
private:
	u1 tag;	//��־�ó������е�һ��
public:
	explicit ConstantInfo(u1 t);
    virtual ~ConstantInfo();
	u1 getTag();
};

/**
 * tagΪ3�������Ǹ�λ��ǰ�洢��4�ֽڵ�intֵ
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
 * tagΪ4�������Ǹ�λ��ǰ�洢��4�ֽڵ�floatֵ
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
 * tagΪ5�������Ǹ�λ��ǰ��8�ֽڵ�longֵ
 * 8�ֽ�ռ�ó�������������λ�ã������赱ǰ����Ϊ5������һ��ĵ�������7��ʼ
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
 * tagΪ6�������Ǹ�λ��ǰ��8�ֽڵ�doubleֵ
 * 8�ֽ�����ռ��������λ��
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
 * tagΪ1�����������2�ֽڵ��ַ�������length���Լ�����Ϊlength���ӽڵ��ַ���
 * �ַ����в��ܰ���null�򲹳��ַ���ԭ����class�ļ�����MUTF-8��ʽ���룬��C++���ñ�׼��UTF-8
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
	string decodeMUTF8(const u1* bytearr);	//��utf-8ת����UTF-16�����ʽ
	string wstring2string(const wstring& wstr);
};

/**
 * tagΪ8��������2�ֽڵ�����ֵ����ָ��CONSTANT_UTF8_INFO���͵�һ��ֵ
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
 * tagΪ7�����������ֽڵ�����index����Ҳָ��CONSTANT_UTF8_INFO���͵�һ��ֵ
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
 * tagΪ12��������������ֵ��2�ֽڵ�����index1��ָ��CONSTANT_UTF8_INFO�����ֶλ򷽷�������
 * 2�ֽڵ�����index2��ָ��CONSTANT_UTF8_INFO�����ֶλ򷽷������������ֶε����͡������Ĳ����б������뷵��ֵ���ͣ�
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
 * tagΪ9��10��11����ʾ�ֶΡ��������ӿڷ��������ߵı�����ʽһ��
 * ����������ֵ������2�ֽڣ��ֱ�ָ��CONSTANT_CLASS_INFO��CONSTANT_NameAndType_INFO
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
 * tagΪ15
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
 * �����أ�ʵ���Ͼ���һ������
 */
class ConstantPool
{
private:
	u2 constant_pool_count;
	vector<ConstantInfo*> cp;	//�ͷ��ڴ�
public:
	explicit ConstantPool(ClassReader& reader);
	~ConstantPool();

	u2 getConstantPoolCount() const;
	ConstantInfo* getConstantInfo(u2 index) const;	//�õ�ָ������λ�õ���

	//һ�������ֶΡ��������ӿڷ�������ConstantMemberInfo���ĵڶ���ֵ
	//���õ�����string���ͣ��ֱ��ʾ�����ƺ�������
	void getNameAndType(string* buf,u2 index) const;	

	//һ������ConsatntMemberInfo�ĵ�һ��ֵ
	//���õ�����
	string getClssName(u2 index) const;

	string& getUtf8(u2 index) const;
};