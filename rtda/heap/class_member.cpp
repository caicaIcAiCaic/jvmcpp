#include"class.h"

ClassMember::ClassMember(MemberInfo* memberinfo, Class* c)
{
	accessFlag = memberinfo->getAccessFlags();
	name = memberinfo->getName();
	descriptor = memberinfo->getDescriptor();
	_class = c;
}
bool ClassMember::isStatic()
{
	return 0 != (accessFlag & ACC_STATIC);
}
bool ClassMember::isPublic()
{
	return 0 != (accessFlag & ACC_PUBLIC);
}
bool ClassMember::isProtected()
{
	return 0 != (accessFlag & ACC_PROTECTED);
}
bool ClassMember::isPrivate()
{
	return 0 != (accessFlag & ACC_PRIVATE);
}
bool ClassMember::isLongOrDouble()
{
	return descriptor == "J" || descriptor == "D";
}
bool ClassMember::isFinal()
{
	return 0 != (accessFlag & ACC_FINAL);
}
bool ClassMember::isNative()
{
	return 0 != (accessFlag & ACC_NATIVE);
}

//1������ֶ�Ϊpublic���������඼���Է���
//2������ֶ�Ϊprotected����ֻ�������ͬһ�����е�����Է���
//3������ֶβ���˽�еģ�ȱʡ�ģ�����ֻ��ͬһ�����е�����Է���
bool ClassMember::isAccessibleTo(Class* d)
{
	if (isPublic()) return true;
	if (isProtected()) return d == _class || d->isSubClassOf(_class) || d->getPackageName() == _class->getPackageName();
	if (!isPrivate()) return d->getPackageName() == _class->getPackageName();
	return d == _class;
}

bool ClassMember::isAbstract()
{
	return 0 != (accessFlag & ACC_ABSTRACT);
}

string ClassMember::getName()
{
	return name;
}
string ClassMember::getDescriptor()
{
	return descriptor;
}
Class* ClassMember::getClass()
{
	return _class;
}

Field::Field(MemberInfo* memberinfo, Class* c) :ClassMember(memberinfo,c)
{
	ConstantValueAttribute* cvl = (ConstantValueAttribute*)memberinfo->getAttribute("ConstantValue");
	if (cvl != nullptr)
	{	//˵�����ֶ���final���壬�ڳ�������������ֵ
		constValueIndex = cvl->getConstantValueIndex();
	}
}

vector<Field*> Field::newFields(ClassFile* cf, Class* c)
{
	vector<Field*> fields = vector<Field*>();
	unsigned short fieldCount = cf->getFieldCount();
	vector<MemberInfo*> fieldsInClassfile = cf->getFields();
	for (int i = 0; i < fieldCount; i++)
	{
		fields.push_back(new Field(fieldsInClassfile[i],c));
	}
	return fields;
}

void Field::setSlotId(unsigned int s)
{
	slotId = s;
}
unsigned int Field::getSlotId()
{
	return slotId;
}

unsigned int Field::getConstValueIndex()
{
	return constValueIndex;
}

vector<Method*> Method::newMethods(ClassFile* cf, Class* c)
{
	vector<Method*> methods = vector<Method*>();
	u2 methodCount = cf->getMethodCount();
	vector<MemberInfo*> methodInClassfile = cf->getMethods();
	for (int i = 0; i < methodCount; i++)
	{
		methods.push_back(new Method(methodInClassfile[i],c));
	}
	return methods;
}
Method::Method(MemberInfo* memberinfo, Class* c) :ClassMember(memberinfo,c)
{
	//�õ�Code�ֽ�������
	CodeAttribute* codeAttr = (CodeAttribute*)memberinfo->getAttribute("Code");
	if (codeAttr != nullptr)
	{
		maxLocals = codeAttr->getMaxLocals();	//�ֲ����������󳤶�
		maxStack = codeAttr->getMaxStack();	//������ջ��������
		code_length = codeAttr->getCodeLength();	//�ֽ��볤��

        u1* tmp = codeAttr->getCode();		//�õ�Code�ֽ��룬����classload.parse���� classfile����ᱻ����
        byteCode = new u1[code_length];
        for (int i = 0; i < code_length; i++) {
            byteCode[i] = tmp[i];
        }

        vector<ExceptionTableEntry> exTable = codeAttr->getExceptionTable();
		int len = exTable.size();
		RunTimeConstantPool* rtcp = c->getRunTimeConstantPool();
		for (int i = 0; i < len; i++)
		{
			ExceptionHandler handler;
			ExceptionTableEntry entry = exTable[i];
			handler.startPC = entry.startPc;
			handler.endPC = entry.endPc;
			handler.handlerPC = entry.handlerPc;
			//���ָ������ʱ�����ص�����Ϊ0�����ʾ���Դ��������쳣
			handler.catchType = entry.catchType == 0 ? nullptr : (ClassRefInfo*)rtcp->getConstant(entry.catchType);
			exceptionTable.push_back(handler);
		}

		lineNumberTable = (LineNumberTableAttribute*)codeAttr->getAttribute("LineNumberTable");
	}
	else
	{
		maxLocals = 0;
		maxStack = 0;
		byteCode = nullptr;
		code_length = 0;
	}
    //��������(��������)����ֵ����
	MethodDescriptor parasedDescriptor = MethodDescriptorParser::parseMethodDescriptor(getDescriptor());
	calcArgSlotCount(parasedDescriptor.parameterTypes);
	if (isNative()) injectCodeAttribute(parasedDescriptor.returnType);
}

void Method::injectCodeAttribute(string returnType)
{
	maxStack = 4;
	maxLocals = argSlotCount;
	switch (returnType[0])
	{
	case 'V':byteCode = new u1[2]{ 0xfe,0xb1 }; break;
	case 'D':byteCode = new u1[2]{ 0xfe,0xaf }; break;
	case 'F':byteCode = new u1[2]{ 0xfe,0xae }; break;
	case 'J':byteCode = new u1[2]{ 0xfe,0xad }; break;
	case 'L':
	case '[':byteCode = new u1[2]{ 0xfe,0xb0 }; break;
	default:byteCode = new u1[2]{ 0xfe,0xac }; break;	//ireturn
	}
}

void Method::calcArgSlotCount(vector<string> parameterTypes)
{
	argSlotCount = 0;
	for (string paramType : parameterTypes)
	{
		argSlotCount++;
		if (paramType == "J" || paramType == "D") argSlotCount++;
	}
	if (!isStatic()) argSlotCount++;	//���Ǿ�̬��������Ҫ���ϵ�һ������this����
}

int Method::findExceptionHandler(Class* exClass, int pc)
{
	for (ExceptionHandler handler : exceptionTable)
	{
		if (pc >= handler.startPC && pc < handler.endPC)
		{
			if (handler.catchType == nullptr) return handler.handlerPC;	//catch-all,��ʾ���Դ��������쳣
			Class* catchClass = handler.catchType->resolvedClass();
			if (catchClass == exClass || exClass->isSubClassOf(catchClass)) return handler.handlerPC;
		}
	}
	return -1;
}

int Method::getLineNumber(int pc)
{
	if (isNative()) return  -2;
	if (lineNumberTable == nullptr) return -1;
	return lineNumberTable->getLineNumber(pc);
}

u2 Method::getMaxStack()
{
	return maxStack;
}
u2 Method::getMaxLocals()
{
	return maxLocals;
}
u4 Method::getCodeLength()
{
	return code_length;
}
u1* Method::getCode()
{
	return byteCode;
}
u4 Method::getArgSlotCount()
{
	return argSlotCount;
}


