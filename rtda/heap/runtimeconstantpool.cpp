#include"class_loader.h"

Constant::Constant(int t):tag(t)
{
}

IntInfo::IntInfo(int t, int v) :Constant(t)
{
	value = v;
}

FloatInfo::FloatInfo(int t, float v) : Constant(t)
{
	value = v;
}

LongInfo::LongInfo(int t, long long v) : Constant(t)
{
	value = v;
}

DoubleInfo::DoubleInfo(int t, double v) : Constant(t)
{
	value = v;
}

StringInfo::StringInfo(int t, string v) : Constant(t)
{
	value = v;
}

SymRefInfo::SymRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c) : Constant(t)
{
	rtcp = cp;
	className = name;
	_class = c;
}
Class* SymRefInfo::resolvedClass()
{
	if (_class == nullptr) resolveClassRef();
	return _class;
}
void SymRefInfo::resolveClassRef()
{
	Class* d = rtcp->getClass();
	Class* c = d->getClassLoader()->loadClass(className);
	if (!c->isAccessibleTo(d)) {
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}
	_class = c;
}


ClassRefInfo::ClassRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c) : SymRefInfo(t, cp, name, c)
{

}

MemberRefInfo::MemberRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d) : SymRefInfo(t, cp, name, c)
{
	this->name = n;
	descriptor = d;
}

FieldRefInfo::FieldRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Field* f) :MemberRefInfo(t, cp, name, c, n, d)
{
	field = f;
}

Field* FieldRefInfo::resolvedField()
{
	if (field == nullptr) resolveFieldRef();
	return field;
}

void FieldRefInfo::resolveFieldRef()
{
	Class* d = rtcp->getClass();
	Class* c = resolvedClass();	//解析字段之前首先解析类，然后根据字段名与描述符查找字段，如果查找成功，并且有访问权限
								//则返回该字段
	Field* f = lookupField(c, name, descriptor);
	if (f == nullptr) {
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}
	if (!f->isAccessibleTo(d))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	field = f;
}

//要查找类C中是否有字段name：
//			1、首先早该类的字段中查找
//			2、否则在该类的接口中查找
//			3、最后在该类的父类中查找
//			4、都查找不到则返回NULL
Field* FieldRefInfo::lookupField(Class* c, string name, string descriptor)
{
	vector<Field*> fields = c->getFields();
	for (int i = 0; i < fields.size(); i++)
	{
		if (fields[i]->getName() == name && fields[i]->getDescriptor() == descriptor) return fields[i];
	}

	vector<Class*> interfaces = c->getInterfaces();
	for (int i = 0; i < interfaces.size(); i++)
	{
		Field* temp = lookupField(interfaces[i], name, descriptor);
		if (temp != nullptr) return temp;
	}

	if (c->getSuperClass() != nullptr) return lookupField(c->getSuperClass(), name, descriptor);

	return nullptr;
}


MethodRefInfo::MethodRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Method* m) : MemberRefInfo(t, cp, name, c, n, d)
{
	method = m;
}

Method* MethodRefInfo::resolvedMethod()
{
	if (method == nullptr) resolveMethodRef();
	return method;
}
void MethodRefInfo::resolveMethodRef()
{
	//解析方法符号引用之前首先解析类，然后根据方法名与描述符查找，并且查看有访问权限
	Class* d = rtcp->getClass();
	Class* c = resolvedClass();

	if (c->isInterface())	//只解析非接口方法 是接口方法则抛出异常
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	Method* m = lookupMethod(c, name, descriptor);
	if (m == nullptr) {
		cout << "java.lang.NoSuchMethodError" << endl;
		exit(0);
	}
	if (!m->isAccessibleTo(d))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}

	method = m;
}

Method* MethodRefInfo::lookupMethod(Class* c, string name, string descriptor)
{
	Method* m = lookupMethodInClass(c, name, descriptor);
	if (m == nullptr) m = lookupMethodInInterfaces(c->getInterfaces(), name, descriptor);
	return m;
}
Method* MethodRefInfo::lookupMethodInClass(Class* c, string name, string descriptor)
{
	while (c != nullptr)
	{
		vector<Method*> methods = c->getMethods();
		for (unsigned int i = 0; i < methods.size(); i++)
		{
			if (methods[i]->getName() == name && methods[i]->getDescriptor() == descriptor) return methods[i];
		}
		c = c->getSuperClass();
	}
}
Method* MethodRefInfo::lookupMethodInInterfaces(vector<Class*>ifaces, string name, string descriptor)
{
	for (Class* iface : ifaces)
	{
		for (Method* m : iface->getMethods())
		{
			if (m->getName() == name && m->getDescriptor() == descriptor) return m;
		}
        //在从该类实现的接口的父接口中查找
		Method* m = lookupMethodInInterfaces(iface->getInterfaces(), name, descriptor);
		if (m != nullptr) return m;
	}
	return nullptr;
}


InterfaceMethodRefInfo::InterfaceMethodRefInfo(int t, RunTimeConstantPool* cp, string name, Class* c, string n, string d, Method* m) : MemberRefInfo(t, cp, name, c, n, d)
{
	method = m;
}
Method* InterfaceMethodRefInfo::resolvedInterfaceMethod()
{
	if (method == nullptr) resolveInterfaceMethodRef();
	return method;
}
void InterfaceMethodRefInfo::resolveInterfaceMethodRef()
{
	Class* d = rtcp->getClass();
	Class* iface = resolvedClass();

	if (!iface->isInterface())	//只解析接口方法 不是接口则抛出异常
	{
		cout << "java.lang.IncompatibleClassChangeError" << endl;
		exit(0);
	}

	Method* m = lookupInterfaceMethod(iface, name, descriptor);
	if (m == nullptr) {
		cout << "java.lang.NoSuchMethodError" << endl;
		exit(0);
	}
	if (!m->isAccessibleTo(d))
	{
		cout << "java.lang.IllegalAccessError" << endl;
		exit(0);
	}
	method = m;
}
Method* InterfaceMethodRefInfo::lookupInterfaceMethod(Class* iface, string name, string descriptor)
{
	for (Method* m : iface->getMethods())	//首先在本接口中寻找方法
	{
		if (m->getName() == name && m->getDescriptor() == descriptor) return m;
	}
	//如果在接口中找不到方法，就在超接口中寻找
	return MethodRefInfo::lookupMethodInInterfaces(iface->getInterfaces(), name, descriptor);
}



RunTimeConstantPool::RunTimeConstantPool(Class* c, const ConstantPool* cp)
{
	_class = c;

	constant_pool_count = cp->getConstantPoolCount();
	consts = vector<Constant*>(constant_pool_count);

	for (int i = 1; i < constant_pool_count; i++)	//常量池的索引从1开始到constant_pool_count - 1结束
	{
		ConstantInfo* ci = cp->getConstantInfo(i);	//动态链接：将Class文件中的各种符号引用转换成真正的内存地址
		unsigned char tag = ci->getTag();

		if (tag == 3)	//int值
		{
			int value = ((ConstantIntegerInfo*)ci)->getVal();
			IntInfo* temp = new IntInfo(3, value);
			consts[i] = temp;
		}
		else if (tag == 4)
		{
			float value = ((ConstantFloatInfo*)ci)->getVal();
			FloatInfo* temp = new FloatInfo(4, value);
			consts[i] = temp;
		}
		else if (tag == 5)
		{
			long long value = ((ConstantLongInfo*)ci)->getVal();
			LongInfo* temp = new LongInfo(5, value);
			consts[i] = temp;
			i++;		//long类型与double类型占用两个索引位置
		}
		else if (tag == 6)
		{
			double value = ((ConstantDoubleInfo*)ci)->getVal();
			DoubleInfo* temp = new DoubleInfo(6, value);
			consts[i] = temp;
			i++;
		}
		else if (tag == 8)
		{
			string value = cp->getUtf8(((ConstantStringInfo*)ci)->getIndex());
			StringInfo* temp = new StringInfo(8, value);
			consts[i] = temp;
		}
		else if (tag == 7)
		{
			string name = cp->getUtf8(((ConstantClassInfo*)ci)->getNameIndex());
			ClassRefInfo* temp = new ClassRefInfo(7, this, name, nullptr);
			consts[i] = temp;
		}
		else if (tag == 9)
		{
			string className = cp->getClssName(((ConstantMemberrefInfo*)ci)->getClassIndex());
			string NameAndDecriptor[2];
			cp->getNameAndType(NameAndDecriptor, ((ConstantMemberrefInfo*)ci)->getNameAndTypeIndex());
			FieldRefInfo* temp = new FieldRefInfo(9, this, className, nullptr, NameAndDecriptor[0], NameAndDecriptor[1], NULL);
			consts[i] = temp;
		}
		else if (tag == 10)
		{
			string className = cp->getClssName(((ConstantMemberrefInfo*)ci)->getClassIndex());
			string NameAndDecriptor[2];
			cp->getNameAndType(NameAndDecriptor, ((ConstantMemberrefInfo*)ci)->getNameAndTypeIndex());
			MethodRefInfo* temp = new MethodRefInfo(10, this, className, nullptr, NameAndDecriptor[0], NameAndDecriptor[1], NULL);
			consts[i] = temp;
		}
		else if (tag == 11)
		{
			string className = cp->getClssName(((ConstantMemberrefInfo*)ci)->getClassIndex());
			string NameAndDecriptor[2];
			cp->getNameAndType(NameAndDecriptor, ((ConstantMemberrefInfo*)ci)->getNameAndTypeIndex());
			InterfaceMethodRefInfo* temp = new InterfaceMethodRefInfo(10, this, className, nullptr, NameAndDecriptor[0], NameAndDecriptor[1], NULL);
			consts[i] = temp;
		}
	}

}
RunTimeConstantPool::~RunTimeConstantPool()
{
	for (int i = 0; i < consts.size(); i++) delete consts[i];
}


Class* RunTimeConstantPool::getClass()
{
	return _class;
}

Constant* RunTimeConstantPool::getConstant(unsigned int index)
{
	Constant* c = consts[index];
	if (c == nullptr) {
		cout << "NO constants at index:" << index << endl;
		exit(0);
	}
	return c;
}