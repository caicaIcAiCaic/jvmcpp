//#define _HAS_STD_BYTE 0

#include"string_pool.h"
#include <Windows.h>

unordered_map<string, Object*> StringPool::internedStrings;

Object* StringPool::JString(ClassLoader* loader, string cppStr)
{
	if (internedStrings.find(cppStr) != internedStrings.end())
		return internedStrings.find(cppStr)->second;

	//�õ�utf16��ʽ���ַ���
    wstring wstr = string2wstring(cppStr);
	const wchar_t* c = wstr.c_str();

    wchar_t* chars = new wchar_t[wstr.size()];
	for (int i = 0; i < wstr.size(); i++) chars[i] = c[i];

	//����һ��Object�����൱��value���飬���Java�ַ�����ֵ
	Object* jChars = new Object(loader->loadClass("[C"), chars, wstr.size());	
	//����һ��java.lang.String������������Ԫ�أ�����һ��ָ��value���飬����һ������hashֵ���������ַ����Ĺ�ϣֵ
	Object* jStr = loader->loadClass("java/lang/String")->newObject();
	jStr->SetRefVar("value", "[C", jChars);

	internedStrings.insert({ cppStr,jStr });
	return jStr;
}

string StringPool::cppString(Object* jStr)
{
	Object* charArr = jStr->GetRefVar("value", "[C");	//�õ�String������value����
    wchar_t* cs = charArr->getChars();
    
    wchar_t* ws = new wchar_t[charArr->getArrayLength() + 1];
    for (int i = 0; i < charArr->getArrayLength(); i++) ws[i] = cs[i];
    ws[charArr->getArrayLength()] = '\0';

    wstring wstr = wstring(ws);    //value���鲻�洢��������������Ҫ�ֶ����
    return wstring2string(wstr);
}

//��stringת����wstring  
wstring StringPool::string2wstring(string str)
{
    wstring result;
    //��ȡ��������С��������ռ䣬��������С���ַ�����  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    wchar_t * buffer = new wchar_t [len + 1];
    //���ֽڱ���ת���ɿ��ֽڱ���  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //����ַ�����β  
    //ɾ��������������ֵ
    result.append(buffer);
    delete[] buffer;
    return result;
}

//��wstringת����string  
string StringPool::wstring2string(wstring wstr)
{
    string result;
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

Object* StringPool::internString(Object* jStr)
{
    string cppStr = cppString(jStr);
    auto internedStr = internedStrings.find(cppStr);
    if (internedStr != internedStrings.end()) return internedStr->second;
    
    internedStrings.insert({ cppStr,jStr });
    return jStr;
}

