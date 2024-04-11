#pragma once
#include"memberInfo.h"

using std::cout;
using std::endl;

//��Ŀ¼��Ҫʵ��һ�����׵�javap���ߣ�JDK�����ṩ��һ������ǿ��������й���javap
//�����Է�����class�ļ����ó�����ľ�����Ϣ

//���ļ��ṹ
//ּ����������Class�ṹ�壬һ��Class����ʱ���ݽṹ�ڷ��������ɣ��ö����û����
class ClassFile
{
private:
	u4 magic;
	u2 minorVersion;
	u2 majorVersion;

	ConstantPool* constantPool;	//������C++���Ա�Ĺ���˳�򣬶����Աһ������ͨ��Ա���ȹ��죬����ֻ��ʹ��ָ��

	u2 accessFlags;

	u2 thisClass;	//��ָ��һ��constant_class_info����������
	u2 superClass;
	u2 interfaceCount;
	vector<u2> interfaces;

	u2 fieldCount;
	vector<MemberInfo*> fields;		//�ͷſռ�
	u2 methodCount;
	vector<MemberInfo*> methods;	//�ͷ�

//	u2 attributes_count;
    vector<AttributeInfo*> attributes;
//	AttributeInfo** attributes;	//class�ļ�������

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
	AttributeInfo* getAttribute(string name);	//����class�ļ���ָ�����Ƶ����ԣ��޴������򷵻�NULL

private:
    void readAndCheckMagic(ClassReader& reader);
    void readAndCheckVersion(ClassReader& reader);
};