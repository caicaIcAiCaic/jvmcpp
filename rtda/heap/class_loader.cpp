#include"string_pool.h"
#include<iterator>

const unordered_map<string, string> primitiveTypes = {
	{"void","V"},
	{"boolean","Z"},
	{"byte","B"},
	{"short","S"},
	{"int","I"},
	{"long","J"},
	{"char","C"},
	{"float","F"},
	{"double","D"}
};

ClassLoader::ClassLoader(ClassPath* _cp, bool verboseClassFlag):cp(_cp),verboseFlag(verboseClassFlag)
{
	loadBasicClasses();	    //加载java/lang/Class类
	loadPrimitiveClasses(); //加载基本数据类型
}

Class* ClassLoader::loadClass(string name)
{
	auto it = classMap.find(name);
	if(it != classMap.end()) return it->second;//此类加载器已经加载过了name类,直接返回
	
	Class* c;
	if (name[0] == '[') c =  loadArrayClass(name);
	else c = loadNonArrayClass(name);

	//当类信息成功写入方法区后，创建该类的java/lang/Class实例，并与方法区关联
	//即为方法区中的类信息生成一个java/lang/Class对象实例
	auto jlClassClass = classMap.find("java/lang/Class");
	if (jlClassClass != classMap.end())
	{
		c->setJClass(jlClassClass->second->newObject());
		c->getJClass()->setExtra(c);
	}
	
	return c;
}

Class* ClassLoader::loadArrayClass(string& name)
{
	Class* c = new Class(name,this,loadClass("java/lang/Object"));	//数组的父类是Object类

	vector<Class*> interfaces;		//数组实现了java/lang/Cloneable和java/io/Serializable
	interfaces.push_back(loadClass("java/lang/Cloneable"));
	interfaces.push_back(loadClass("java/io/Serializable"));
	c->setInterfaces(interfaces);

	classMap.insert({ name,c });
	return c;
}
//类的加载大致分为三个步骤：首先找到class文件并将数据读到内存
//							然后解析class文件，生成虚拟机可以使用的类数据，并放入方法区
//							最后进行链接
Class* ClassLoader::loadNonArrayClass(string& name)
{
	vector<u1>data = readClass(name); //字节流
	Class* _class = defineClass(name,data);	//生成Class类对象、加载父类、接口
	link(_class);	//分配静态变量、实例变量空间、为静态变量赋0值，初始化静态常量

	if(verboseFlag)
		cout << "[loaded " << name  << "]" << endl;
	return _class;
}

//readClass方法只是调用了classpath的readClass方法，并进行了错误处理
vector<u1> ClassLoader::readClass(string& name)
{
	vector<unsigned char> data = cp->readClass(name);
	if (data.empty()) {
		cout << "java.lang.ClassNotFoundException: " << name << endl;
		exit(0);
	}
	return data;
}

Class* ClassLoader::defineClass(string& name,vector<unsigned char>& data)
{
	Class* _class = parseClass(data);	//生成Class类
	_class->setClassLoader(this);	//定义类加载器
	resolveSuperClass(_class);
	resolveInterfaces(_class);
	classMap.insert({ name,_class });
	return _class;
}
Class* ClassLoader::parseClass(vector<unsigned char>& data)
{
	ClassReader reader = ClassReader(data);
	ClassFile cf = ClassFile(reader);	//解析字节码，生成class对象
	return new Class(&cf);
}
void ClassLoader::link(Class* _class)
{
	verify(_class);
	prepare(_class);
}

void ClassLoader::verify(Class* _class)
{

}
void ClassLoader::prepare(Class* _class)
{
	calcInstanceFieldSlotIds(_class);
	calcStaticFieldSlotIds(_class);
	allocAndInitStaticVars(_class);
}


void ClassLoader::resolveSuperClass(Class* _class)	//加载父类
{
	if (_class->getName() != "java/lang/Object") {
		_class->setSuperClass(_class->getClassLoader()->loadClass(_class->getSuperClassName()));
	}
}
void ClassLoader::resolveInterfaces(Class* _class)	//加载接口
{
	vector<string> interfaceNames = _class->getInterfaceName();
	vector<Class*> interfaces;
	for (unsigned int i = 0; i < interfaceNames.size(); i++)
	{
		interfaces.push_back(_class->getClassLoader()->loadClass(interfaceNames[i]));
	}
	_class->setInterfaces(interfaces);
}
// 从它的父类开始，为每一个字段赋一个id字段
void ClassLoader::calcInstanceFieldSlotIds(Class* c)
{
	unsigned int slotId = 0;
	if (c->getSuperClass() != nullptr)	//Object类
	{
		slotId = c->getSuperClass()->getInstanceSlotCount();
	}
	vector<Field*> fields = c->getFields();
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (!fields[i]->isStatic())
		{
			fields[i]->setSlotId(slotId);
			slotId++;
			if (fields[i]->isLongOrDouble()) slotId++;
		}
	}
	c->setInstanceSlotCount(slotId);
}
// 静态字段不能被继承，只关注当前的类即可
void ClassLoader::calcStaticFieldSlotIds(Class* c)
{
	unsigned int slotId = 0;

	//静态变量不能继承
	vector<Field*> fields = c->getFields();
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (fields[i]->isStatic())	//是实例变量
		{
			fields[i]->setSlotId(slotId);
			slotId++;
			if (fields[i]->isLongOrDouble()) slotId++;
		}
	}
	c->setStaticSlotCount(slotId);
}
void ClassLoader::allocAndInitStaticVars(Class* c)
{
	c->setStaticVars(new Slots(c->getStaticSlotCount()));
	vector<Field*> fields = c->getFields();
	for (unsigned int i = 0; i < fields.size(); i++)	//其实这里是有一个赋0值的过程，但是槽位slot在构造时已经被赋好0值了
	{													//所以这里只处理final即可
		if (fields[i]->isStatic() && fields[i]->isFinal())	//如果静态变量属于基本数据类型或string类型，有final修饰，且它
		{													//的值在编译期可知，那么该值存储在常量池中
			initStaticFinalVar(c, fields[i]);
		}
	}
}

void ClassLoader::initStaticFinalVar(Class* c,Field* field)
{
	Slots* vars = c->getStaticVars();
	RunTimeConstantPool* rtcp = c->getRunTimeConstantPool();
	unsigned int cpIndex = field->getConstValueIndex();
	unsigned int slotId = field->getSlotId();

	if (cpIndex > 0) {
		string descriptor = field->getDescriptor();
		if (descriptor == "Z") vars->setInt(slotId, ((IntInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "B") vars->setInt(slotId, ((IntInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "C") vars->setInt(slotId, ((IntInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "S") vars->setInt(slotId, ((IntInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "I") vars->setInt(slotId, ((IntInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "F") vars->setFloat(slotId, ((FloatInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "J") vars->setLong(slotId, ((LongInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "D") vars->setDouble(slotId, ((DoubleInfo*)rtcp->getConstant(cpIndex))->value);
		if (descriptor == "Ljava/lang/String;") {
			string cppStr = ((StringInfo*)rtcp->getConstant(cpIndex))->value;
			Object* jStr = StringPool::JString(c->getClassLoader(), cppStr);
			vars->setRef(slotId, jStr);
		}
	}
}

void ClassLoader::loadBasicClasses()
{
	Class* jlClassClass = loadClass("java/lang/Class");	//加载java.lang.Class类
	//加载java.lang.Class会触发java.lang.Object以及其他接口的加载
	//需要给已经加载的每一个类关联类对象
	for (auto c : classMap)
	{
		if (c.second->getJClass() == nullptr)
		{
			c.second->setJClass(jlClassClass->newObject());	//使方法区中的类信息指向java/lang/Class实例
			c.second->getJClass()->setExtra(c.second);	//再使该Class实例指向方法区中的类信息
		}
	}
}
void ClassLoader::loadPrimitiveClasses()
{
	for (const auto& primitiveType : primitiveTypes)
	{
		string cn = primitiveType.first;	//类名是int、void等等
		Class* c = new Class(cn, this, nullptr);

		c->setJClass(classMap.find("java/lang/Class")->second->newObject());    //指向一个java.lang.Class对象
		c->getJClass()->setExtra(c);    //设置java.lang.Class对象指向int的运行时数据结构
		classMap.insert({ cn,c });
	}
}
