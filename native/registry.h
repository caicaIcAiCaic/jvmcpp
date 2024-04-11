#pragma once
#include<unordered_map>
#include"../rtda/frame.h"

using std::unordered_map;
//���庯��ָ�룬PFΪָ������ָ��
typedef void(*PF)(Frame*);

void emptyNativeMethod(Frame* frame);

//ע��Ͳ��ұ��ط���
class REGISTRY
{
private:
	//���ط���ע���
	static unordered_map<string, PF> registry;
public:
	static void init();
	//�������������ͷ�������������һ�����Ψһȷ��һ������
	static void Register(string className, string methodName, string methodDescriptor, PF method);
	//�������������������������������ұ��ط�����ʵ��
	static PF FindNativeMethod(string className, string methodName, string methodDescriptor);
};


