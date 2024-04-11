#include"class_loader.h"
#include<unordered_map>

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

Class::Class(string& name, ClassLoader* cl, Class* sc):initStarted(true),accessFlags(ACC_PUBLIC),className(name),loader(cl),superClass(sc)
{

}

Class::Class(ClassFile* cf):initStarted(false),jClass(nullptr),loader(nullptr),superClass(nullptr)
{
	const ConstantPool* cp = cf->getConstantPool();
	accessFlags = cf->getAccessFlags();
	className = cp->getClssName(cf->getThisClass());
	superClassName = cp->getClssName(cf->getSuperClass());

	interfaceCount = cf->getInterfaceCount();
    interfaceNames.reserve(interfaceCount);
	for (int i = 0; i < interfaceCount; i++) {		//将该classfile中的接口名全部添加
//		interfaceNames[i] = cp->getClssName(cf->getInterfaces()[i]);
        interfaceNames.push_back(cp->getClssName(cf->getInterfaces()[i]));
	}

	rtcp = new RunTimeConstantPool(this,cp);
	fieldCount = cf->getFieldCount();
	fields = Field::newFields(cf,this);
	methodCount = cf->getMethodCount();
	methods = Method::newMethods(cf,this);
	
	sourceFile = getSourceFile(cf);
}

string Class::getSourceFile(ClassFile* cf)
{
	SourceFileAttribute* sfAttr = dynamic_cast<SourceFileAttribute*>(cf->getAttribute("SourceFile"));
	if (sfAttr != nullptr) return sfAttr->getSourceFile();
	return "Unknown SourceFile Name";	//并不是每个class文件都有源文件信息，因编译时的编译期选项而异
}

Object* Class::newObject()
{
	return new Object(this, new Slots(instanceSlotCount));
}
Object* Class::newArray(int count)
{
	//如果该Class对象不是数组，则终止程序
	if (!isArray())
	{
		cout << "Not array class: " << className << endl;
		exit(0);
	}
    Object* obj = nullptr;
	if (className == "[Z") obj = count == 0 ? new Object(this, new char [count],count) :
                                        new Object(this, new char [count]{0},count);
	else if (className == "[B") obj = count == 0 ? new Object(this, new char [count],count) :
                                      new Object(this, new char [count]{0},count);
	else if (className == "[C") obj = count == 0 ? new Object(this, new wchar_t [count],count) :
                                      new Object(this, new wchar_t [count]{0},count);
	else if (className == "[S") obj = count == 0 ? new Object(this, new short [count],count) :
                                      new Object(this, new short [count]{0},count);
	else if (className == "[I") obj = count == 0 ? new Object(this, new int [count],count) :
                                      new Object(this, new int [count]{0},count);
	else if (className == "[J") obj = count == 0 ? new Object(this, new long long [count],count) :
                                      new Object(this, new long long [count]{0},count);
	else if (className == "[F") obj = count == 0 ? new Object(this, new float [count],count) :
                                      new Object(this, new float [count]{0},count);
	else if (className == "[D") obj = count == 0 ? new Object(this, new double [count],count) :
                                      new Object(this, new double [count]{0},count);
	else
        obj = count == 0 ? new Object(this, new Object * [count],count) :
                new Object(this, new Object * [count]{nullptr},count);
    return obj;
}

//在三种情况下other类型的引用值可以赋值给this类型
//1、other和this是同一类型
//2、this是类且other是this的子类
//3、this是接口且other实现了接口this
//4、数组可以强制转换成Object、cloneable和serializable类型
//5、如果下列条件成立，则[]sc可以强制转换成[]tc：
//		sc和tc是同一个数据类型或者sc可以强制转换成tc
bool Class::isAssignableFrom(Class* other)
{
	Class *s = other, *t = this;
	if (s == t) return true;
	
	if (!s->isArray())  //不是数组
	{
		if (!s->isInterface())
		{
			if (!t->isInterface()) return s->isSubClassOf(t);
			else return s->isImplements(t);
		}
		else
		{
			if (!t->isArray())
			{
				if (!t->isInterface()) return t->isJlObject();
				else return s->isSubInterfaceOf(t);
			}
		}
	}
	else
	{
		if (!t->isArray())
		{
			if (!t->isInterface()) return t->isJlObject();
			else return t->isJlCloneable() || t->isJioSerializable();
		}
		else
		{
			Class* sc = s->componentClass();
			Class* tc = t->componentClass();
			return sc == tc || tc->isAssignableFrom(sc);
		}
	}

	return false;
}
/**
 * 判断this类是否是other的子类
 * @param other
 * @return
 */
bool Class::isSubClassOf(Class* other)
{
	for (Class* c = superClass; c != nullptr; c = c->superClass)
	{
		if (c == other) return true;
	}
	return false;
}
/**
 * this类是否实现了iface接口
 * @param iface
 * @return
 */
bool Class::isImplements(Class* iface)
{
	for (Class* c = this; c != nullptr; c = c->superClass)
	{
        vector<Class*> tmp = c->getInterfaces();
		for (auto i : tmp)
		{	//判断this是否实现了iface接口，就看this或this的父类是否实现了iface接口或该接口的子接口
			if (iface == i || i->isSubInterfaceOf(iface)) return true;
		}
	}
	return false;
}
/**
 * 递归判断该接口是否是iface的子接口
 * @param iface
 * @return
 */
bool Class::isSubInterfaceOf(Class* iface)
{
	for (auto interface : interfaces)
	{
		if (interface == iface || interface->isSubInterfaceOf(iface)) return true;
	}
	return false;
}
/**
 *
 * @return className == "java/lang/Object"
 */
bool Class::isJlObject()
{
	return className == "java/lang/Object";
}
bool Class::isJlCloneable()
{
	return className == "java/lang/Cloneable";
}
bool Class::isJioSerializable()
{
	return className == "java/io/Serializable";
}
bool Class::isPublic()
{
	return 0 != (accessFlags & ACC_PUBLIC);
}
bool Class::isFinal()
{
	return 0 != (accessFlags & ACC_FINAL);
}
bool Class:: isSuper()
{
	return 0 != (accessFlags & ACC_SUPER);
}
bool Class::isInterface()
{
	return 0 != (accessFlags & ACC_INTERFACE);
}
bool Class::isAbstract()
{
	return 0 != (accessFlags & ACC_ABSTRACT);
}
bool Class::isSynthetic()
{
	return 0 != (accessFlags & ACC_SYNTHETIC);
}
bool Class::isAnnotation()
{
	return 0 != (accessFlags & ACC_ANNOTATION);
}
bool Class::isEnum()
{
	return 0 != (accessFlags & ACC_ENUM);
}
bool Class::isArray()
{
	return className[0] == '[';
}
// 该类是否可以被other访问：该类是public、或者两个类在同一个包内
bool Class::isAccessibleTo(Class* other)
{
	return isPublic() || getPackageName() == other->getPackageName();
}
//该类是否是基本数据类型
bool Class::isPrimitive()
{
	if (primitiveTypes.find(className) != primitiveTypes.end()) return true;
	return false;
}

//返回类对应的数组名
//以当前元素作为组件元素，在外面加上“一维”作为数组
Class* Class::getArrayClass()
{
	string arrayClassName;
	if (className[0] == '[') arrayClassName = "[" + className;
	else if (primitiveTypes.find(className) != primitiveTypes.end()) arrayClassName = "[" + primitiveTypes.find(className)->second;
	else arrayClassName = "[L" + className + ";";
	return loader->loadClass(arrayClassName);
}

Class* Class::componentClass()	//根据数组名得出数组元素名（可以被类加载器加载）
{
	string componentClassName = getComponentClassName();
	return loader->loadClass(componentClassName);
}
string Class::getComponentClassName()
{
	if (className[0] == '[')
	{
		string descriptor = className.substr(1);
		return toClassName(descriptor);
	}
	cout << "Not array: " << className << endl;
	exit(0);
}
string Class::toClassName(string descriptor)
{
	if (descriptor[0] == '[') return descriptor;	//array
	if (descriptor[0] == 'L') return descriptor.substr(1, descriptor.size() - 2);	//object
	for (const auto& temp : primitiveTypes)
	{
		if (temp.second == descriptor) return temp.first;
	}
	cout << "Invalid descriptor: " << descriptor << endl;
	exit(0);
}

Method* Class::getMainMethod()
{
	return getStaticMethod("main", "([Ljava/lang/String;)V");
}
Method* Class::getClinitMethod()
{
	return getStaticMethod("<clinit>", "()V");
}
/**
 * 返回该类中指定的静态方法
 * @param name 方法名称
 * @param descriptor 方法描述符
 * @return Method* or nullptr
 */
Method* Class::getStaticMethod(string name, string descriptor)
{
	for (int i = 0; i < methodCount; i++)
	{
		if (methods[i]->isStatic() && methods[i]->getName() == name && methods[i]->getDescriptor() == descriptor)
			return methods[i];
	}
	return nullptr;
}
Method* Class::getInstanceMethod(string name, string descriptor)
{
	return getMethod(name, descriptor, false);
}

string Class::getPackageName()
{
	size_t i = className.find_last_of('/');
	if (i == string::npos) return "";
	return className.substr(0, i);
}
// 返回该类的java.lang.Class对象
Object* Class::getJClass()
{
	return jClass;
}
void Class::setJClass(Object* jc)
{
	jClass = jc;
}

string Class::getName()
{
	return className;
}
string Class::getSuperClassName()
{
	return superClassName;
}
int Class::getInterfaceCount()
{
	return interfaceCount;
}
vector<string>& Class::getInterfaceName()
{
	return interfaceNames;
}

string Class::getSourceFile()
{
	return sourceFile;
}

RunTimeConstantPool* Class::getRunTimeConstantPool()
{
	return rtcp;
}
void Class::setRunTimeConstantPool(RunTimeConstantPool* cp)
{
	rtcp = cp;
}


Field* Class::getField(string name, string descriptor, bool isStatic)
{
	for (Class* c = this; c != nullptr; c = c->superClass)
	{
		vector<Field*> fs = c->getFields();
		for (Field* f : fs)
		{
			if (f->isStatic() == isStatic && f->getName() == name && f->getDescriptor() == descriptor)
				return f;
		}
	}
	return nullptr;
}

vector<Field*>& Class::getFields()
{
	return fields;
}

Method* Class::getMethod(string name, string descriptor, bool isStatic)
{
	for (Class* c = this; c != nullptr; c = c->superClass)
	{
		for (Method* m : methods)
		{
			if (m->isStatic() == isStatic && m->getName() == name && m->getDescriptor() == descriptor)
				return m;
		}
	}
	return nullptr;
}

vector<Method*>& Class::getMethods()
{
	return methods;
}

Class* Class::getSuperClass()
{
	return superClass;
}
void Class::setSuperClass(Class* _class)
{
	superClass = _class;
}

vector<Class*>& Class::getInterfaces()
{
	return interfaces;
}
void Class::setInterfaces(vector<Class*> interf)
{
	interfaces = interf;
}

ClassLoader* Class::getClassLoader()
{
	return loader;
}
void Class::setClassLoader(ClassLoader* cl)
{
	loader = cl;
}

unsigned int Class::getInstanceSlotCount()
{
	return instanceSlotCount;
}
void Class::setInstanceSlotCount(unsigned int count)
{
	instanceSlotCount = count;
}

unsigned int Class::getStaticSlotCount()
{
	return staticSlotCount;
}
void Class::setStaticSlotCount(unsigned int count)
{
	staticSlotCount = count;
}

Slots* Class::getStaticVars()
{
	return staticVars;
}
void Class::setStaticVars(Slots* s)
{
	staticVars = s;
}
Object* Class::getRefVar(string name, string descriptor)
{
	Field* f = getField(name, descriptor, true);
	return staticVars->getRef(f->getSlotId());
}

bool Class::InitStarted()
{
	return initStarted;
}
void Class::StartInit()
{
	initStarted = true;
}

string Class::JavaName()
{
	string name = className;
	for (string::size_type pos(0); pos != string::npos; pos++)
	{
		if ((pos = name.find('/')) != string::npos) name.replace(pos, 1, ".");
		else break;
	}
	return name;
}
