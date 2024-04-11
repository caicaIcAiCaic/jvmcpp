#pragma once
#include"../../classpath/classpath.h"
#include"class.h"
#include<unordered_map>

using std::unordered_map;
//����ʵ��һ�����װ���������
//ClassLoader����classpath�������Ͷ�ȡclass�ļ�
class ClassLoader
{
private:
	ClassPath* cp;	//����classpathָ��
	unordered_map<string, Class*> classMap;	//�����Ѿ������ع����࣬k�������ȫ�޶���
	bool verboseFlag;
	//���ڿ��԰�classMap�����Ƿ������ľ���ʵ��
public:
	ClassLoader(ClassPath* _cp, bool verboseClassFlag);
	Class* loadClass(string name);
private:
	//����������ͨ���кܴ������������ݲ�������class�ļ���������JVM�������ڼ�����
	Class* loadArrayClass(string& name);
	Class* loadNonArrayClass(string& name); //����loadClass�������ã����س�������֮�����

	vector<u1> readClass(string& name);		//��ȡ�ֽ����ļ�
	Class* defineClass(string& name,vector<u1>& data);	//����Class���󡢼��ظ��ࡢ�ӿ�

	Class* parseClass(vector<u1>& data);	//����Class�ṹ��
	void resolveSuperClass(Class* _class);	//����ö���ĸ��಻��Object����������ظ���
	void resolveInterfaces(Class* _class);	//�������ƣ��ݹ�ļ��ؽӿ�
	
	void link(Class* _class);

	void verify(Class* _class);		//�����е���֤�׶�
	void prepare(Class* _class);	//�����е�׼���׶�

	void calcInstanceFieldSlotIds(Class* c);	//����ʵ���ֶεĸ���
	void calcStaticFieldSlotIds(Class* c);	//���㾲̬�ֶεĸ���
	void allocAndInitStaticVars(Class* c);	//�����������ռ䲢����ֵ

	void initStaticFinalVar(Class* c, Field* field);	//׼���׶� ����final���εľ�̬������ֵ

	void loadBasicClasses();    //����Class��
	void loadPrimitiveClasses();    //���ػ����������ͣ�int��char��void�ȵ�
};



