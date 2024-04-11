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

//1、如果字段为public，则所有类都可以访问
//2、如果字段为protected，则只有子类和同一个包中的类可以访问
//3、如果字段不是私有的（缺省的），则只有同一个包中的类可以访问
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
	{	//说明该字段由final定义，在常量池中有其数值
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
	//得到Code字节码属性
	CodeAttribute* codeAttr = (CodeAttribute*)memberinfo->getAttribute("Code");
	if (codeAttr != nullptr)
	{
		maxLocals = codeAttr->getMaxLocals();	//局部变量表的最大长度
		maxStack = codeAttr->getMaxStack();	//操作数栈的最大深度
		code_length = codeAttr->getCodeLength();	//字节码长度

        u1* tmp = codeAttr->getCode();		//得到Code字节码，参数classload.parse方法 classfile对象会被销毁
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
			//如果指向运行时常量池的索引为0，则表示可以处理所有异常
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
    //描述符：(方法参数)返回值类型
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
	if (!isStatic()) argSlotCount++;	//不是静态方法，需要加上第一个参数this引用
}

int Method::findExceptionHandler(Class* exClass, int pc)
{
	for (ExceptionHandler handler : exceptionTable)
	{
		if (pc >= handler.startPC && pc < handler.endPC)
		{
			if (handler.catchType == nullptr) return handler.handlerPC;	//catch-all,表示可以处理所有异常
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


