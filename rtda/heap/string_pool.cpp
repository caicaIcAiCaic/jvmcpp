//#define _HAS_STD_BYTE 0

#include"string_pool.h"
#include <Windows.h>

unordered_map<string, Object*> StringPool::internedStrings;

Object* StringPool::JString(ClassLoader* loader, string cppStr)
{
	if (internedStrings.find(cppStr) != internedStrings.end())
		return internedStrings.find(cppStr)->second;

	//得到utf16格式的字符串
    wstring wstr = string2wstring(cppStr);
	const wchar_t* c = wstr.c_str();

    wchar_t* chars = new wchar_t[wstr.size()];
	for (int i = 0; i < wstr.size(); i++) chars[i] = c[i];

	//生成一个Object，它相当与value数组，存放Java字符串的值
	Object* jChars = new Object(loader->loadClass("[C"), chars, wstr.size());	
	//生成一个java.lang.String对象，它有两个元素，其中一个指向value数组，另外一个就是hash值，缓存中字符串的哈希值
	Object* jStr = loader->loadClass("java/lang/String")->newObject();
	jStr->SetRefVar("value", "[C", jChars);

	internedStrings.insert({ cppStr,jStr });
	return jStr;
}

string StringPool::cppString(Object* jStr)
{
	Object* charArr = jStr->GetRefVar("value", "[C");	//得到String对象中value数组
    wchar_t* cs = charArr->getChars();
    
    wchar_t* ws = new wchar_t[charArr->getArrayLength() + 1];
    for (int i = 0; i < charArr->getArrayLength(); i++) ws[i] = cs[i];
    ws[charArr->getArrayLength()] = '\0';

    wstring wstr = wstring(ws);    //value数组不存储结束符，所以需要手动添加
    return wstring2string(wstr);
}

//将string转换成wstring  
wstring StringPool::string2wstring(string str)
{
    wstring result;
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    wchar_t * buffer = new wchar_t [len + 1];
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值
    result.append(buffer);
    delete[] buffer;
    return result;
}

//将wstring转换成string  
string StringPool::wstring2string(wstring wstr)
{
    string result;
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

Object* StringPool::internString(Object* jStr)
{
    string cppStr = cppString(jStr);
    auto internedStr = internedStrings.find(cppStr);
    if (internedStr != internedStrings.end()) return internedStr->second;
    
    internedStrings.insert({ cppStr,jStr });
    return jStr;
}

