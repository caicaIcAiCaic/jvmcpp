#pragma once
#include "lib\cmdline.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

//简易版命令行工具，用于启动JVM是设置参数
class cmd
{
private:
	bool versionFlag;

	string cpOption;	//指定用户类路径，在多个包的情况下需要使用';'分割
	string XjreOption;	//指定jre的路径：启动类路径jre\lib、扩展类路径jre\lib\ext
	string className;	//指定类名

	bool verboseClassFlag;	//是否打印类加载信息至控制台
	bool verboseInstFlag;	//是否将指令执行信息输出至控制台

	vector<string> args;

public:
	cmd(int argc, char* argv[]);
	cmd(const char  *xjre, const char *cp, const char *cn); // 提供字符串字面量

	void printUsage();
	bool getVersionFlag();
    string& getCpOption();
	string& getClassName();
    string& getJreOption();
	bool getVerboseClassFlag();
	bool getVerboseInstFlag();
    vector<string>& getArgs();
};



