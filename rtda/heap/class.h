#pragma once
#include "runtimeconstantpool.h"
#include "slots.h"

//ClassFile����Ϊ��ʵ������ع��ܶ����ӵ��м�㣬�ڱ�Ŀ¼�У�����Ҫ��һ������ClassFile����
//����ת��ΪClass���󣬲����뷽����

//��Class�����У���Ҫ��һ��ָ�����������ָ��
//�������������ClassLoader�У�Ҳ��Ҫ������Class��ָ��
//����ǰ�����õ����⣬����Class����ֻ�������������get��set�����������ڱ������ǰ������
class ClassLoader;

//��������
class Class
{
private:
	bool initStarted;	//��ʾ�����<clinit>�����Ƿ��Ѿ�ִ�й���: ��NEWָ��ִ��ʱ�ж�
	Object* jClass;	    //ָ��java.lang.Classʵ��

	unsigned short accessFlags;

	string className;					//����
	string superClassName;				//������

	int interfaceCount;
	vector<string>interfaceNames;			//�ӿ�����

	RunTimeConstantPool* rtcp;	    //ǰ����������

	int fieldCount;
	vector<Field*> fields;						//�ֶα�
	int methodCount;
	vector<Method*> methods;					//������

	string sourceFile;	//Դ�ļ�����

	ClassLoader* loader;		//loader�ֶδ���������
	Class* superClass;			//����ָ��
	vector<Class*> interfaces;	//�ӿ�ָ��

	unsigned int instanceSlotCount;	//������Ĵ�С
	unsigned int staticSlotCount;	//ʵ�������Ĵ�С
	Slots* staticVars;		//��ž�̬����,Ϊ��̬��������ռ䲢����ʼֵ��������ص�׼���׶�

public:
	//�ù��캯����Ĭ�Ͻ���ʶ����Ϊpublic��initStartedΪtrue
	Class(string& name,ClassLoader* cl,Class* sc);	//��������ʱ
	Class(ClassFile* cf);

    string getSourceFile(ClassFile* cf);

	Object* newObject();
	Object* newArray(int count);	//�����������

	bool isAssignableFrom(Class* other);	//other���������Ƿ���Ը�ֵ��this����
	bool isSubClassOf(Class* other);	    //�����Ƿ���other������
	bool isImplements(Class* iface);	    //�����Ƿ�ʵ����iface�ӿ�
	bool isSubInterfaceOf(Class* iface);	//�жϸýӿ��Ƿ���iface���ӽӿ�
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

	Class* getArrayClass();	//�����������ͣ��õ������Ԫ������
	Class* componentClass();
	string getComponentClassName();
	string toClassName(string descriptor);

	Method* getMainMethod();	//�õ������main��������û���ҵ�main�������򷵻�NULL
	Method* getClinitMethod();	//��ȡclinit����
	Method* getStaticMethod(string name,string descriptor);
	Method* getInstanceMethod(string name, string descriptor);
	string getPackageName();	//�õ��������ڵİ�������

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
