#pragma once
#include"../../classpath/classpath.h"
#include"class.h"
#include<unordered_map>

using std::unordered_map;
//初步实现一个简易版的类加载器
//ClassLoader依赖classpath来搜索和读取class文件
class ClassLoader
{
private:
	ClassPath* cp;	//保存classpath指针
	unordered_map<string, Class*> classMap;	//保存已经被加载过的类，k是类的完全限定名
	bool verboseFlag;
	//现在可以把classMap当作是方法区的具体实现
public:
	ClassLoader(ClassPath* _cp, bool verboseClassFlag);
	Class* loadClass(string name);
private:
	//数组类与普通类有很大区别，它的数据不来自于class文件，而是由JVM在运行期间生成
	Class* loadArrayClass(string& name);
	Class* loadNonArrayClass(string& name); //它被loadClass方法调用，加载除数组类之外的类

	vector<u1> readClass(string& name);		//读取字节流文件
	Class* defineClass(string& name,vector<u1>& data);	//生成Class对象、加载父类、接口

	Class* parseClass(vector<u1>& data);	//生成Class结构体
	void resolveSuperClass(Class* _class);	//如果该对象的父类不是Object，则继续加载父类
	void resolveInterfaces(Class* _class);	//作用类似，递归的加载接口
	
	void link(Class* _class);

	void verify(Class* _class);		//链接中的验证阶段
	void prepare(Class* _class);	//链接中的准备阶段

	void calcInstanceFieldSlotIds(Class* c);	//计算实例字段的个数
	void calcStaticFieldSlotIds(Class* c);	//计算静态字段的个数
	void allocAndInitStaticVars(Class* c);	//给类变量分配空间并赋零值

	void initStaticFinalVar(Class* c, Field* field);	//准备阶段 对用final修饰的静态变量赋值

	void loadBasicClasses();    //加载Class类
	void loadPrimitiveClasses();    //加载基本数据类型：int、char、void等等
};



