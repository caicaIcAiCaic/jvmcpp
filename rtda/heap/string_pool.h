#pragma once
#include"class_loader.h"

class StringPool
{
private:
	static unordered_map<string, Object*>internedStrings;
public:
	//根据传递进来的c++字符串返回Java形式的字符串
	static Object* JString(ClassLoader* loader, string cppStr);
	static string cppString(Object* jStr);	//将JavaString对象转换成c++字符串

	static wstring string2wstring(string str);
	static string wstring2string(wstring wstr);

	//如果字符串没有放入池中，就放入字符串并返回，否则返回找到的已入池的字符串
	static Object* internString(Object* jStr);
};


