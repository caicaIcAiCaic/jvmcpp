#pragma once
#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef struct MethodDescriptor {
	vector<string> parameterTypes;
	string returnType;
}MethodDescriptor;

class MethodDescriptorParser
{
private:
	string raw;
	int offset;
	MethodDescriptor parsed;
public:
	static MethodDescriptor parseMethodDescriptor(string descriptor);

private:
	MethodDescriptor parse(string descriptor);

	void startParams();
	void endParams();

	void finish();
	void causePanic();

	unsigned char readUint8();
	void unreadUint8();

	void parseParamTypes();
	void parseReturnType();

	string parseFieldType();
	string parseObjectType();
	string parseArrayType();
};


