#include"method_descriptor.h"

MethodDescriptor MethodDescriptorParser::parseMethodDescriptor(string descriptor)
{
	MethodDescriptorParser p;
	return p.parse(descriptor);
}

MethodDescriptor MethodDescriptorParser::parse(string descriptor)
{
	raw = descriptor;
	offset = 0;
	startParams();	//查看首个字符是否正确
	parseParamTypes();
	endParams();	//参数列表要以')'结束
	parseReturnType();
	finish();
	return parsed;
}

void MethodDescriptorParser::startParams()
{
	if (readUint8() != '(') causePanic();
}

void MethodDescriptorParser::endParams()
{
	if (readUint8() != ')') causePanic();
}

void MethodDescriptorParser::finish()
{
	if (offset != raw.size()) causePanic();
}

void MethodDescriptorParser::causePanic()
{
	cout << "BAD descriptor: " << raw << endl;
	exit(0);
}

unsigned char MethodDescriptorParser::readUint8()
{
	return raw[offset++];
}

void MethodDescriptorParser::unreadUint8()
{
	offset--;
}

void MethodDescriptorParser::parseParamTypes()
{
	while (true)
	{
		string t = parseFieldType();
		if(t != "" ){
			parsed.parameterTypes.push_back(t);
		}
		else break;
	}
}

void MethodDescriptorParser::parseReturnType()
{
	if(readUint8() == 'V') {
		parsed.returnType = "V";
		return;
	}

	unreadUint8();
	string t = parseFieldType();
	if (t != "" ){
		parsed.returnType = t;
		return;
	}

	causePanic();
}

string MethodDescriptorParser::parseFieldType()
{
	switch (readUint8()) {
	case 'B':
		return "B";
	case 'C':
		return "C";
	case 'D':
		return "D";
	case 'F':
		return "F";
	case 'I':
		return "I";
	case 'J':
		return "J";
	case 'S':
		return "S";
	case 'Z':
		return "Z";
	case 'L':
		return parseObjectType();
	case '[':
		return parseArrayType();
	default:
		unreadUint8();
		return "";
	}
}
string MethodDescriptorParser::parseObjectType()
{
	auto semicolonIndex = raw.find(';',offset);	//寻找offset之后;所在的位置
	if (semicolonIndex == string::npos ){	//如果引用参数类型不是以;结束，则给出的参数列表是不合法的
		causePanic();
		return "";
	}
	else {
		int objStart = offset - 1;
		int objEnd =  semicolonIndex + 1;
		offset = objEnd;
		return raw.substr(objStart, objEnd);	//返回LJava/lang/String;
	}
}
string MethodDescriptorParser::parseArrayType()
{
	int arrStart = offset - 1;
	parseFieldType();	//具体的数组类型
	int arrEnd = offset;
	return raw.substr(arrStart, arrEnd);
}
