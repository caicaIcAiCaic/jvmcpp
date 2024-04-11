#pragma once
#include"entry.h"

class ClassPath
{
private:
	Entry* bootClasspath;
	Entry* extClasspath;
	Entry* userClasspath;
public:
	ClassPath(string& jreOption, string& cpOption);	//xJre��classpath
    ~ClassPath();	//�ͷ��ڴ�

	//readClass(string)�������δӣ�������·������չ��·�����û���·����ȡ�ļ�
	//���className�����ڣ��򷵻ص�vector�ĳ���Ϊ0
	vector<unsigned char> readClass(string& className);
	string getJreDir(string& jreOption);
	string toString();
};
