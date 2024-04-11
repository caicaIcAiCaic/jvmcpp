#include"entry.h"

/**
 * entry��ķ���ʵ��
 */
const char Entry::pathSeparator = std::filesystem::path::preferred_separator;
const char Entry::listSeparator = ';';

vector<string> Entry::split(string& str, char separator)
{
	vector<string> strs;
	string::size_type begin = 0, pos = 0;
	pos = str.find(separator, begin);
	while (pos != string::npos)
	{
		strs.push_back(str.substr(begin, pos - begin));
		begin = pos + 1;
		pos = str.find(separator, begin);
	}
	strs.push_back(str.substr(begin, str.size() - begin));
	return strs;
}
/**
 * to ensure the path is exits
 * if the path not exits, don't return, just ends
 * @param path
 */
void Entry::surePathExits(string& path)	//�ж�·���Ƿ����
{
	if (!std::filesystem::exists(path))
	{
		cout << "path: " << path << " not found!" << endl;
		exit(0);
	}
}
/**
 * destruction must be virtual
 */
Entry::~Entry() noexcept = default;

/**
 * dirEntry���캯��
 * @param path
 */
DirEntry::DirEntry(string path): Entry(),absDir(path)
{
	surePathExits(path);
	absDir = std::filesystem::absolute(absDir);	//��·��ת��Ϊ����·��
}
/**
 * override from entry:: readClass
 * @param className
 * @return bytes.size() maybe == 0, if not find this class from this absDir
 */
vector<unsigned char> DirEntry::readClass(string& className)
{
	vector<unsigned char> bytes;
	std::ifstream fin;
	std::filesystem::path fileName = absDir / className;	//��Ŀ¼��������ϳ��ļ�·��

	fin.open(fileName.string(), std::ios_base::binary);
	if (fin.good())
	{
		char buffer = 0;
		while (fin.get(buffer))
		{
			bytes.push_back(buffer);
		}
	}
	fin.close();
	return bytes;
}
/**
 *
 * @return the absolute file path
 */
string DirEntry::toString()
{
	return absDir.string();
}
DirEntry::~DirEntry() noexcept = default;

ZipEntry::ZipEntry(string path): Entry(), absPath(path)
{
	surePathExits(path);
	absPath = std::filesystem::absolute(absPath);
}
/**
 * read class
 * @param className
 * @return if class not exits, vector<unsigned char>'s size could be 0
 */
vector<unsigned char> ZipEntry::readClass(string& className)
{
	vector<unsigned char> bytes;
	void* buf = nullptr;	//������
	size_t bufsize = 0;
	zip_t* zip = zip_open(absPath.string().c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
	{
		zip_entry_open(zip, className.c_str());	//��zip��jar�д�ָ���ļ�
		{
			zip_entry_read(zip, &buf, &bufsize);
		}
		zip_entry_close(zip);
	}
	zip_close(zip);
	unsigned char* s = static_cast<unsigned char*>(buf);

    bytes.reserve(bufsize); //��ǰ����ռ�
    for (int i = 0; i < bufsize; i++)
	{
		bytes.push_back(s[i]);
	}

	free(buf);	//�ͷŻ������ڴ�
	return bytes;
}
string ZipEntry::toString()
{
	return absPath.string();
}
ZipEntry::~ZipEntry() noexcept = default;

WildcardEntry::WildcardEntry(string wildPath): Entry()
{
	wildPath.pop_back();	//ȥ��*
	for (auto& p : std::filesystem::directory_iterator(wildPath))
	{
		if (p.path().filename().string().find(".zip") != string::npos || p.path().filename().string().find(".jar") != string::npos)	//���ļ�������zip��jar
		{
			zips.emplace_back(ZipEntry(p.path().string()));
		}
	}
}
/**
 *
 * @param className
 * @return if class not exits, return vector's size is emtpy()
 */
vector<unsigned char> WildcardEntry::readClass(string& className)
{
	vector<unsigned char> bytes;
	for (auto & zip : zips)
	{
		bytes = zip.readClass(className);
		if (!bytes.empty())
			return bytes;
	}
	return bytes;
}
string WildcardEntry::toString()
{
	string str;
	if (!zips.empty()) {
		for (auto & zip : zips)
		{
			str.append(zip.toString() + Entry::listSeparator);
		}
		str.pop_back();
	}
	return str;
}
WildcardEntry::~WildcardEntry() noexcept = default;

/**
 * constructor of CompositeEntry
 * @param pathList
 */
CompositeEntry::CompositeEntry(string pathList)
{
	vector<string> paths = Entry::split(pathList, Entry::listSeparator);
	for (auto & path : paths)
	{
		if (path.find(".zip") != string::npos || path.find(".jar") != string::npos)	//������Ƿ���ѹ����·��
		{
			ZipEntry* e = new ZipEntry(path);
			entrys.push_back(e);
		}
		else if (path.find('*') != string::npos)	//�Ƿ���ͨ���·��
		{
			WildcardEntry* e = new WildcardEntry(path);
			entrys.push_back(e);
		}
		else  //����·��
		{
			DirEntry* e = new DirEntry(path);
			entrys.push_back(e);
		}
	}
}
CompositeEntry::~CompositeEntry()
{
    for (auto iter : entrys)
    {
        delete iter;
    }
}
/**
 *
 * @param className
 * @return if class not exits, the return vector cloud be empty
 */
vector<unsigned char> CompositeEntry::readClass(string& className)
{
	vector<unsigned char> bytes;
	for (auto entry : entrys)
	{
		bytes = entry->readClass(className);
		if (!bytes.empty())
			return bytes;
	}
	return bytes;
}
string CompositeEntry::toString()
{
	string str;
	if (!entrys.empty()) {
		for (auto iter : entrys)
		{
			str.append(iter->toString() + Entry::listSeparator);
		}
		str.pop_back();
	}
	return str;
}




