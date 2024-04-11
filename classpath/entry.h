#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "..\lib\zip.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

/***
 *  entry �������͵Ļ���
 */
class Entry
{
public:
	const static char pathSeparator;	//��ȡ��ǰ����ϵͳĿ¼�ָ���,unix��'/' windows:'/'��'\';
	const static char listSeparator;	//���Ŀ¼�ķָ���
public:
	vector<string> split(string& str, char separator);	//�����ʹ��';'�ָ��Ŀ¼�ֿ�
    void surePathExits(string& path);	//�ж�·���Ƿ����
	virtual vector<unsigned char> readClass(string& className) = 0;	//����������������Ӧ��class�ļ������ض�ȡ���ֽ���
	virtual string toString() = 0;
    virtual ~Entry();
};

/**
 * dirEntry: ��ʾĿ¼��ʽ����·����������Ҳ������ͨ��Ŀ¼���磺D:\java\space
 */
class DirEntry : public Entry
{
private:
	std::filesystem::path absDir;	//���Ŀ¼�ľ���·��
public:
	explicit DirEntry(string path);
	vector<unsigned char> readClass(string& className) override;	//�ڴ�Ŀ¼�£�Ѱ����ΪclassName���ļ����������ֽ���
	string toString() override;
    ~DirEntry() override;
};

/**
 * ��ʾZIP��JAR�ļ���ʽ����·��
 */
class ZipEntry :public Entry
{
private:
	std::filesystem::path absPath;	//���ZIP�ļ���JAR�ļ��ľ���·��
public:
	explicit ZipEntry(string path);
	vector<unsigned char> readClass(string& className) override;	//��ѹ����zip��jar�ж�ȡ��ΪclassName��class�ļ�
	string toString() override;
    ~ZipEntry() override;
};

/**
 * ��ͨ���(*)ָ��ĳ��Ŀ¼�µ�����JAR�ļ�
 * java -cp classes;lib\*
 */
class WildcardEntry : public Entry
{
private:
	vector<ZipEntry> zips;	//���ö�������ʱ���������ͷ�vector��ָ����ָ����ڴ棬������Ҫ�ֶ��ͷ�
public:
	explicit WildcardEntry(string wildPath);	//����ָ����Ŀ¼���õ���Ŀ¼�����е�jar/zip�ļ���·��
	vector<unsigned char> readClass(string& className) override;	//�ڸ�Ŀ¼�µ�����jar/zip�ļ��ж�ȡclass�ļ�
	string toString() override;
    ~WildcardEntry() override;
};

/**
 * ͬʱָ�����Ŀ¼���ļ������÷ָ����ֿ�
 * java -cp path\to\classes;lib\a.jar;lib\b.jar;lib\c.zip...
 */
class CompositeEntry :public Entry
{
private:
	vector<Entry*> entrys;	//����·������ϣ�ʹ��';'�ָ�

public:
	explicit CompositeEntry(string pathList);
    ~CompositeEntry() override;
	vector<unsigned char> readClass(string& className) override;
	string toString() override;
};



