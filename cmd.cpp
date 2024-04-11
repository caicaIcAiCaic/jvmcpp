#include "cmd.h"

cmd::cmd(int argc, char* argv[])
{
	cmdline::parser p;	//创建命令行解析器

	p.add("version");
	p.add<string>("cp");
	p.add<string>("xjre");
	p.add("verboseClassFlag");
	p.add("verboseInstFlag");


	p.parse_check(argc, argv);	//解析命令行

	this->versionFlag = p.exist("version");
	this->cpOption = p.get<string>("cp");
	this->XjreOption = p.get<string>("xjre");

	this->verboseClassFlag = p.exist("verboseClassFlag");
	this->verboseInstFlag = p.exist("verboseInstFlag");


	//获取其余未解析的参数,并将类名赋给className
	if (!p.rest().empty()) {
		this->className = p.rest()[0];

		if (p.rest().size() > 1) {
			this->args.assign(p.rest().begin() + 1, p.rest().end());
		}
	}

	//将java1.ch01.Test转换成java1/ch01/Test
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = className.find('.')) != string::npos) className.replace(pos, 1, "/");
		else break;
	}
}
/**
 * one of Constructors of cmd
 * @param xjre jre path
 * @param cp user path
 * @param cn classname
 */
cmd::cmd(const char  *xjre, const char *cp, const char *cn):
XjreOption(xjre), cpOption(cp), className(cn), verboseInstFlag(true), verboseClassFlag(true), versionFlag(false)
{

}

void cmd::printUsage()
{	
	cout << "Please enter a class name" << endl;
	cout << "Usage: [-option] class [args...]" << endl;
}

bool cmd::getVersionFlag()
{
	return versionFlag;
}

string& cmd::getCpOption()
{
	return cpOption;
}

string& cmd::getClassName()
{
	return className;
}

string& cmd::getJreOption()
{
	return XjreOption;
}

bool cmd::getVerboseClassFlag()
{
	return verboseClassFlag;
}
bool cmd::getVerboseInstFlag()
{
	return verboseInstFlag;
}

vector<string>& cmd::getArgs()
{
	return args;
}