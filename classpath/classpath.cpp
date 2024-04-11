#include"classpath.h"
/**
 * Constructor of ClassPath
 * @param jreOption jre path
 * @param cpOption user path
 */
ClassPath::ClassPath(string& jreOption, string& cpOption): bootClasspath(nullptr), extClasspath(nullptr),userClasspath(nullptr)
{
	string jre = getJreDir(jreOption);

    //������·����JAVA_HOME/jre/lib/*
	bootClasspath = new WildcardEntry(jre + Entry::pathSeparator + "lib" + Entry::pathSeparator + '*');
	extClasspath = new WildcardEntry(jre + Entry::pathSeparator + "lib" + Entry::pathSeparator + "ext" +
            Entry::pathSeparator + '*');

	if (cpOption.empty())   //�û�·��Ϊ�գ�Ĭ��ʹ�õ�ǰ·��
	{
		cpOption = ".";
	}

    //��ѯ����';'
	if (cpOption.find(Entry::listSeparator) != string::npos)
	{
		userClasspath = new CompositeEntry(cpOption);
	}
	else if (cpOption.find('*') != string::npos)
	{
		userClasspath = new WildcardEntry(cpOption);
	}
	else if (cpOption.find(".zip") != string::npos || cpOption.find(".jar") != string::npos)
	{
		userClasspath = new ZipEntry(cpOption);
	}
	else
	{
		userClasspath = new DirEntry(cpOption);
	}
}

/**
 * readClass(string)�������δӣ�������·������չ��·�����û���·����ȡ�ļ�
 * @param className
 * @return  the vector return must not empty, is class not exists, JVM will exit
 */
vector<unsigned char> ClassPath::readClass(string& className)
{
	string _name = className + ".class";
	vector<unsigned char> bytes = bootClasspath->readClass(_name);
	if (!bytes.empty())
	{
		return bytes;
	}
	bytes = extClasspath->readClass(_name);
	if (!bytes.empty())
	{
		return bytes;
	}
	bytes = userClasspath->readClass(_name);
    if (!bytes.empty())
	{
		return bytes;
	}

    cout << "Can't find this class: " << _name << endl;
    exit(0);
}

ClassPath::~ClassPath()	//�ͷ��ڴ�
{
    delete bootClasspath;
    delete extClasspath;
    delete userClasspath;
}
/**
 * jre folder exists ? if not exists, JVM will exit
 * @param jreOption
 * @return correct jre path
 */
string ClassPath::getJreDir(string& jreOption)
{
    string java_home = string (getenv("JAVA_HOME"));    //��ȡ��������JAVA_HOME

	if (!jreOption.empty() && std::filesystem::exists(jreOption))   //�������jreOptionָ����Ŀ¼�����ֱ�ӷ���
	{
		return jreOption;
	}
	else if (jreOption.empty() && std::filesystem::exists(".\\jre"))	//�û�δָ��jreĿ¼��Ĭ��Ϊ��ǰĿ¼
	{
		return  ".\\jre";
	}
	else if (jreOption.empty() && !java_home.empty() && std::filesystem::exists(java_home))	//��ǰĿ¼������jre�������JAVA_HOME
	{
		java_home.pop_back();
		return java_home;
	}
	else
	{
		cout << "Can't find jre folder!" << endl;
		exit(0);
	}
}
/**
 *
 * @return return bootClassPath, extClassPath, userClassPath
 */
string ClassPath::toString()
{
	return "bootClassPath:" + bootClasspath->toString() + '\n'
		+ "extClassPath:" + extClasspath->toString() + '\n'
		+ "userClassPath:" + userClasspath->toString();
}
