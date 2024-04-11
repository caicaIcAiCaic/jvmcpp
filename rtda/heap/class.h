#pragma once
#include "runtimeconstantpool.h"
#include "slots.h"

//ClassFile类是为了实现类加载功能而增加的中间层，在本目录中，我们要进一步处理ClassFile对象
//将其转变为Class对象，并放入方法区

//在Class对象中，需要有一个指向类加载器的指针
//而在类加载器类ClassLoader中，也需要保存有Class的指针
//存在前向引用的问题，由于Class类中只对类加载器进行get、set操作，所以在本类进行前向声明
class ClassLoader;

//析构函数
class Class
{
private:
	bool initStarted;	//表示该类的<clinit>方法是否已经执行过了: 在NEW指令执行时判断
	Object* jClass;	    //指向java.lang.Class实例

	unsigned short accessFlags;

	string className;					//类名
	string superClassName;				//超类名

	int interfaceCount;
	vector<string>interfaceNames;			//接口类名

	RunTimeConstantPool* rtcp;	    //前向引用问题

	int fieldCount;
	vector<Field*> fields;						//字段表
	int methodCount;
	vector<Method*> methods;					//方法表

	string sourceFile;	//源文件名称

	ClassLoader* loader;		//loader字段存放类加载器
	Class* superClass;			//父类指针
	vector<Class*> interfaces;	//接口指针

	unsigned int instanceSlotCount;	//类变量的大小
	unsigned int staticSlotCount;	//实例变量的大小
	Slots* staticVars;		//存放静态变量,为静态变量分配空间并赋初始值是在类加载的准备阶段

public:
	//该构造函数会默认将标识符置为public，initStarted为true
	Class(string& name,ClassLoader* cl,Class* sc);	//生成数组时
	Class(ClassFile* cf);

    string getSourceFile(ClassFile* cf);

	Object* newObject();
	Object* newArray(int count);	//创建数组对象

	bool isAssignableFrom(Class* other);	//other引用类型是否可以赋值给this类型
	bool isSubClassOf(Class* other);	    //该类是否是other的子类
	bool isImplements(Class* iface);	    //该类是否实现了iface接口
	bool isSubInterfaceOf(Class* iface);	//判断该接口是否是iface的子接口
	bool isJlObject();
	bool isJlCloneable();
	bool isJioSerializable();
	bool isPublic();
	bool isFinal();
	bool isSuper();
	bool isInterface();
	bool isAbstract();
	bool isSynthetic();
	bool isAnnotation();
	bool isEnum();
	bool isArray();
	bool isAccessibleTo(Class* other);
	bool isPrimitive();

	Class* getArrayClass();	//引用数组类型：得到具体的元素类型
	Class* componentClass();
	string getComponentClassName();
	string toClassName(string descriptor);

	Method* getMainMethod();	//得到该类的main方法，若没有找到main方法，则返回NULL
	Method* getClinitMethod();	//获取clinit方法
	Method* getStaticMethod(string name,string descriptor);
	Method* getInstanceMethod(string name, string descriptor);
	string getPackageName();	//得到该类所在的包的名称

	Object* getJClass();
	void setJClass(Object* jc);

	string getName();
	string getSuperClassName();
	int getInterfaceCount();
	vector<string>& getInterfaceName();

	string getSourceFile();

	RunTimeConstantPool* getRunTimeConstantPool();
	void setRunTimeConstantPool(RunTimeConstantPool* cp);

	Field* getField(string name, string descriptor, bool isStatic);
	vector<Field*>& getFields();
	Method* getMethod(string name, string descriptor, bool isStatic);
	vector<Method*>& getMethods();

	Class* getSuperClass();
	void setSuperClass(Class* _class);

	vector<Class*>& getInterfaces();
	void setInterfaces(vector<Class*> interf);

	ClassLoader* getClassLoader();
	void setClassLoader(ClassLoader* cl);

	unsigned int getInstanceSlotCount();
	void setInstanceSlotCount(unsigned int count);

	unsigned int getStaticSlotCount();
	void setStaticSlotCount(unsigned int count);

	Slots* getStaticVars();
	void setStaticVars(Slots* s);
	Object* getRefVar(string name, string descriptor);

	bool InitStarted();
	void StartInit();

	string JavaName();
};
