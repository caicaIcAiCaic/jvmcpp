#pragma once
#include"class_loader.h"

class StringPool
{
private:
	static unordered_map<string, Object*>internedStrings;
public:
	//���ݴ��ݽ�����c++�ַ�������Java��ʽ���ַ���
	static Object* JString(ClassLoader* loader, string cppStr);
	static string cppString(Object* jStr);	//��JavaString����ת����c++�ַ���

	static wstring string2wstring(string str);
	static string wstring2string(wstring wstr);

	//����ַ���û�з�����У��ͷ����ַ��������أ����򷵻��ҵ�������ص��ַ���
	static Object* internString(Object* jStr);
};


