#pragma once
#include "lib\cmdline.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

//���װ������й��ߣ���������JVM�����ò���
class cmd
{
private:
	bool versionFlag;

	string cpOption;	//ָ���û���·�����ڶ�������������Ҫʹ��';'�ָ�
	string XjreOption;	//ָ��jre��·����������·��jre\lib����չ��·��jre\lib\ext
	string className;	//ָ������

	bool verboseClassFlag;	//�Ƿ��ӡ�������Ϣ������̨
	bool verboseInstFlag;	//�Ƿ�ָ��ִ����Ϣ���������̨

	vector<string> args;

public:
	cmd(int argc, char* argv[]);
	cmd(const char  *xjre, const char *cp, const char *cn); // �ṩ�ַ���������

	void printUsage();
	bool getVersionFlag();
    string& getCpOption();
	string& getClassName();
    string& getJreOption();
	bool getVerboseClassFlag();
	bool getVerboseInstFlag();
    vector<string>& getArgs();
};



