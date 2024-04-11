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
 *  entry 所有类型的基类
 */
class Entry
{
public:
	const static char pathSeparator;	//获取当前操作系统目录分隔符,unix：'/' windows:'/'或'\';
	const static char listSeparator;	//多个目录的分隔符
public:
	vector<string> split(string& str, char separator);	//将多个使用';'分割的目录分开
    void surePathExits(string& path);	//判断路径是否存在
	virtual vector<unsigned char> readClass(string& className) = 0;	//传入类名、搜索对应的class文件并返回读取的字节流
	virtual string toString() = 0;
    virtual ~Entry();
};

/**
 * dirEntry: 表示目录形式的类路径：最正常也是最普通的目录，如：D:\java\space
 */
class DirEntry : public Entry
{
private:
	std::filesystem::path absDir;	//存放目录的绝对路径
public:
	explicit DirEntry(string path);
	vector<unsigned char> readClass(string& className) override;	//在此目录下，寻找名为className的文件，并返回字节流
	string toString() override;
    ~DirEntry() override;
};

/**
 * 表示ZIP或JAR文件形式的类路径
 */
class ZipEntry :public Entry
{
private:
	std::filesystem::path absPath;	//存放ZIP文件或JAR文件的绝对路径
public:
	explicit ZipEntry(string path);
	vector<unsigned char> readClass(string& className) override;	//从压缩包zip或jar中读取名为className的class文件
	string toString() override;
    ~ZipEntry() override;
};

/**
 * 用通配符(*)指定某个目录下的所有JAR文件
 * java -cp classes;lib\*
 */
class WildcardEntry : public Entry
{
private:
	vector<ZipEntry> zips;	//当该对象被销毁时，并不会释放vector内指针所指向的内存，所以需要手动释放
public:
	explicit WildcardEntry(string wildPath);	//传入指定的目录，得到该目录下所有的jar/zip文件的路径
	vector<unsigned char> readClass(string& className) override;	//在该目录下的所有jar/zip文件中读取class文件
	string toString() override;
    ~WildcardEntry() override;
};

/**
 * 同时指定多个目录或文件，并用分隔符分开
 * java -cp path\to\classes;lib\a.jar;lib\b.jar;lib\c.zip...
 */
class CompositeEntry :public Entry
{
private:
	vector<Entry*> entrys;	//多种路径的组合，使用';'分割

public:
	explicit CompositeEntry(string pathList);
    ~CompositeEntry() override;
	vector<unsigned char> readClass(string& className) override;
	string toString() override;
};



