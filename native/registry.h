#pragma once
#include<unordered_map>
#include"../rtda/frame.h"

using std::unordered_map;
//定义函数指针，PF为指向函数的指针
typedef void(*PF)(Frame*);

void emptyNativeMethod(Frame* frame);

//注册和查找本地方法
class REGISTRY
{
private:
	//本地方法注册表
	static unordered_map<string, PF> registry;
public:
	static void init();
	//类名、方法名和方法描述符加在一起才能唯一确定一个方法
	static void Register(string className, string methodName, string methodDescriptor, PF method);
	//根据类名、方法名、方法描述符查找本地方法的实现
	static PF FindNativeMethod(string className, string methodName, string methodDescriptor);
};


