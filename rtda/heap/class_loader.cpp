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
	loadBasicClasses();	    //����java/lang/Class��
	loadPrimitiveClasses(); //���ػ�����������
}

Class* ClassLoader::loadClass(string name)
{
	auto it = classMap.find(name);
	if(it != classMap.end()) return it->second;//����������Ѿ����ع���name��,ֱ�ӷ���
	
	Class* c;
	if (name[0] == '[') c =  loadArrayClass(name);
	else c = loadNonArrayClass(name);

	//������Ϣ�ɹ�д�뷽�����󣬴��������java/lang/Classʵ�������뷽��������
	//��Ϊ�������е�����Ϣ����һ��java/lang/Class����ʵ��
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
	Class* c = new Class(name,this,loadClass("java/lang/Object"));	//����ĸ�����Object��

	vector<Class*> interfaces;		//����ʵ����java/lang/Cloneable��java/io/Serializable
	interfaces.push_back(loadClass("java/lang/Cloneable"));
	interfaces.push_back(loadClass("java/io/Serializable"));
	c->setInterfaces(interfaces);

	classMap.insert({ name,c });
	return c;
}
//��ļ��ش��·�Ϊ�������裺�����ҵ�class�ļ��������ݶ����ڴ�
//							Ȼ�����class�ļ����������������ʹ�õ������ݣ������뷽����
//							����������
Class* ClassLoader::loadNonArrayClass(string& name)
{
	vector<u1>data = readClass(name); //�ֽ���
	Class* _class = defineClass(name,data);	//����Class����󡢼��ظ��ࡢ�ӿ�
	link(_class);	//���侲̬������ʵ�������ռ䡢Ϊ��̬������0ֵ����ʼ����̬����

	if(verboseFlag)
		cout << "[loaded " << name  << "]" << endl;
	return _class;
}

//readClass����ֻ�ǵ�����classpath��readClass�������������˴�����
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
	Class* _class = parseClass(data);	//����Class��
	_class->setClassLoader(this);	//�����������
	resolveSuperClass(_class);
	resolveInterfaces(_class);
	classMap.insert({ name,_class });
	return _class;
}
Class* ClassLoader::parseClass(vector<unsigned char>& data)
{
	ClassReader reader = ClassReader(data);
	ClassFile cf = ClassFile(reader);	//�����ֽ��룬����class����
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


void ClassLoader::resolveSuperClass(Class* _class)	//���ظ���
{
	if (_class->getName() != "java/lang/Object") {
		_class->setSuperClass(_class->getClassLoader()->loadClass(_class->getSuperClassName()));
	}
}
void ClassLoader::resolveInterfaces(Class* _class)	//���ؽӿ�
{
	vector<string> interfaceNames = _class->getInterfaceName();
	vector<Class*> interfaces;
	for (unsigned int i = 0; i < interfaceNames.size(); i++)
	{
		interfaces.push_back(_class->getClassLoader()->loadClass(interfaceNames[i]));
	}
	_class->setInterfaces(interfaces);
}
// �����ĸ��࿪ʼ��Ϊÿһ���ֶθ�һ��id�ֶ�
void ClassLoader::calcInstanceFieldSlotIds(Class* c)
{
	unsigned int slotId = 0;
	if (c->getSuperClass() != nullptr)	//Object��
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
// ��̬�ֶβ��ܱ��̳У�ֻ��ע��ǰ���༴��
void ClassLoader::calcStaticFieldSlotIds(Class* c)
{
	unsigned int slotId = 0;

	//��̬�������ܼ̳�
	vector<Field*> fields = c->getFields();
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (fields[i]->isStatic())	//��ʵ������
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
	for (unsigned int i = 0; i < fields.size(); i++)	//��ʵ��������һ����0ֵ�Ĺ��̣����ǲ�λslot�ڹ���ʱ�Ѿ�������0ֵ��
	{													//��������ֻ����final����
		if (fields[i]->isStatic() && fields[i]->isFinal())	//�����̬�������ڻ����������ͻ�string���ͣ���final���Σ�����
		{													//��ֵ�ڱ����ڿ�֪����ô��ֵ�洢�ڳ�������
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
	Class* jlClassClass = loadClass("java/lang/Class");	//����java.lang.Class��
	//����java.lang.Class�ᴥ��java.lang.Object�Լ������ӿڵļ���
	//��Ҫ���Ѿ����ص�ÿһ������������
	for (auto c : classMap)
	{
		if (c.second->getJClass() == nullptr)
		{
			c.second->setJClass(jlClassClass->newObject());	//ʹ�������е�����Ϣָ��java/lang/Classʵ��
			c.second->getJClass()->setExtra(c.second);	//��ʹ��Classʵ��ָ�򷽷����е�����Ϣ
		}
	}
}
void ClassLoader::loadPrimitiveClasses()
{
	for (const auto& primitiveType : primitiveTypes)
	{
		string cn = primitiveType.first;	//������int��void�ȵ�
		Class* c = new Class(cn, this, nullptr);

		c->setJClass(classMap.find("java/lang/Class")->second->newObject());    //ָ��һ��java.lang.Class����
		c->getJClass()->setExtra(c);    //����java.lang.Class����ָ��int������ʱ���ݽṹ
		classMap.insert({ cn,c });
	}
}
