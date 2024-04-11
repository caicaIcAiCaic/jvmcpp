#pragma once
#include"entry.h"

class ClassPath
{
private:
	Entry* bootClasspath;
	Entry* extClasspath;
	Entry* userClasspath;
public:
	ClassPath(string& jreOption, string& cpOption);	//xJre、classpath
    ~ClassPath();	//释放内存

	//readClass(string)方法依次从：启动类路径、扩展类路径、用户类路径读取文件
	//如果className不存在，则返回的vector的长度为0
	vector<unsigned char> readClass(string& className);
	string getJreDir(string& jreOption);
	string toString();
};
