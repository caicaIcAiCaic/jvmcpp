#include"attributes.h"
/**
 * super class AttributeInfo
 * @param an attribute name
 * @param al attribute length in class file (how many bytes?)
 */
AttributeInfo::AttributeInfo(string& an, u4 al):attrName(an), attrLen(al)
{

}
AttributeInfo::~AttributeInfo() noexcept = default;

string AttributeInfo::getAttributeName()
{
	return attrName;
}

u2 AttributeInfo::getAttributeLength()
{
	return attrLen;
}

/**
 *
 * @param reader
 * @param an attribute name
 * @param al attribute length
 */
UnparsedAttribute::UnparsedAttribute(ClassReader& reader,string& an, u4 al) :AttributeInfo(an, al)
{
	int length = getAttributeLength();
	bytes = new u1[length + 1];
	reader.readBytes(bytes,length + 1);
}

UnparsedAttribute::~UnparsedAttribute()
{
	delete[] bytes;
}

DeprecatedAttribute::DeprecatedAttribute(string& an, u4 al) :AttributeInfo(an, al){}

SyntheticAttribute::SyntheticAttribute(string& an, u4 al) :AttributeInfo(an, al){}

/**
 *
 * @param reader
 * @param cp
 * @param an
 * @param al
 */
SourceFileAttribute::SourceFileAttribute(ClassReader& reader,const ConstantPool* cp ,string& an, u4 al) :AttributeInfo(an, al)
{
	u2 sourceFileIndex = reader.readU2();
	sourceFile = cp->getUtf8(sourceFileIndex);
}
string SourceFileAttribute::getSourceFile()
{
	return sourceFile;
}

/**
 *
 * @param reader
 * @param an
 * @param al
 */
ConstantValueAttribute::ConstantValueAttribute(ClassReader& reader, string& an, u4 al) :AttributeInfo(an, al)
{
	constantValueIndex = reader.readU2();
}
u2 ConstantValueAttribute::getConstantValueIndex()
{
	return constantValueIndex;
}

/**
 *
 * @param reader
 * @param an
 * @param al
 */
ExceptionsAttribute::ExceptionsAttribute(ClassReader& reader, string& an, u4 al) :AttributeInfo(an, al)
{
	exceptions_length = reader.readU2();
	exceptionIndexTable = reader.readU2s(exceptions_length);
}

u2 ExceptionsAttribute::getExceptionLength()
{
	return exceptions_length;
}

vector<u2>& ExceptionsAttribute::getExceptionIndexTable()
{
	return exceptionIndexTable;
}

/**
 *
 * @param reader
 * @param an
 * @param al
 */
LineNumberTableAttribute::LineNumberTableAttribute(ClassReader& reader, string& an, u4 al) :AttributeInfo(an, al)
{
	int len = reader.readU2();
	lineNumberTable = vector<LineNumberTableEntry>(len);
	for (int i = 0; i < len; i++)
	{
		lineNumberTable[i].startPc = reader.readU2();
		lineNumberTable[i].lineNumber = reader.readU2();
	}
}
LineNumberTableAttribute::~LineNumberTableAttribute()
= default;

LineNumberTableEntry& LineNumberTableAttribute::getLineNumberTableAt(u2 index)
{
	return lineNumberTable[index];
}
/**
 * 得到pc对应的在源代码中的行号
 * @param pc code属性pc值（bytes）
 * @return 在源文件中对应的行号， 如果找不到则返回-1
 */
int LineNumberTableAttribute::getLineNumber(int pc)
{
	for (int i = lineNumberTable.size() - 1; i >= 0; i--)
	{
		if (lineNumberTable[i].startPc <= pc)
            return (int)lineNumberTable[i].lineNumber;
	}
	return -1;
}

/**
 *  构造函数
 * @param reader 存放字节码
 * @param cp 常量池
 * @param an attribute name
 * @param al attribute在class中的字节长度
 */
LocalVariableTableAttribute::LocalVariableTableAttribute(ClassReader& reader,const ConstantPool* cp ,string& an, u4 al) :AttributeInfo(an, al)
{
    int len = reader.readU2();
    localVariableTable = vector<LocalVariableTableEntry>(len);
	for (int i = 0; i < len; i++)
	{
		localVariableTable[i].startPc = reader.readU2();
		localVariableTable[i].length = reader.readU2();
		localVariableTable[i].name = cp->getUtf8(reader.readU2());
		localVariableTable[i].descriptor = cp->getUtf8(reader.readU2());
		localVariableTable[i].index = reader.readU2();
	}
}
LocalVariableTableAttribute::~LocalVariableTableAttribute()
{
}
/**
 * 返回LocalVariableTableAttribute中的指定索引位置
 * @param index [0, localVariable_length]
 * @return LocalVariableTableEntry
 */
LocalVariableTableEntry& LocalVariableTableAttribute::getLocalVariableTableAt(u2 index)
{
	return localVariableTable[index];
}

/**
 *  方法的code属性
 * @param reader
 * @param cp
 * @param an
 * @param al
 */
CodeAttribute::CodeAttribute(ClassReader& reader, const ConstantPool* cp, string an, u4 al) :AttributeInfo(an, al)
{
	maxStack = reader.readU2();
	maxLocals = reader.readU2();

    code_length = reader.readU4();
	code = new u1[code_length + 1];
	reader.readBytes(code,code_length + 1);	//读取指令字节码

    //读取code属性中异常处理的表
	int exceptionTable_length = reader.readU2();
	exceptionTable = vector<ExceptionTableEntry>(exceptionTable_length);
	for (int i = 0; i < exceptionTable_length; i++)
	{
		exceptionTable[i].startPc = reader.readU2();
		exceptionTable[i].endPc = reader.readU2();
		exceptionTable[i].handlerPc = reader.readU2();
		exceptionTable[i].catchType = reader.readU2();
	}
	
	//code属性中只有三种属性：LineNumberTable、LocalVariableTable、StackMapTable
	int attributes_count = reader.readU2();
	attributes = vector<AttributeInfo*>(attributes_count);
	for (int i = 0; i < attributes_count; i++)
	{
		u2 attr_name_index = reader.readU2();
		u4 attr_length = reader.readU4();

		string attr_Name = cp->getUtf8(attr_name_index);
		if (attr_Name == "LineNumberTable")
		{
			attributes[i] = new LineNumberTableAttribute(reader, attr_Name, attr_length);
		}
		else if (attr_Name == "LocalVariableTable")
		{
			attributes[i] = new LocalVariableTableAttribute(reader,cp, attr_Name, attr_length);
		}
		else
		{
			attributes[i] = new UnparsedAttribute(reader, attr_Name, attr_length);
		}
	}	//end--for
}

CodeAttribute::~CodeAttribute()
{
	delete[] code;
	for (auto & attribute : attributes) delete attribute;
}

u2 CodeAttribute::getMaxStack()
{
	return maxStack;
}

u2 CodeAttribute::getMaxLocals()
{
	return maxLocals;
}

u4 CodeAttribute::getCodeLength()
{
	return code_length;
}

u1* CodeAttribute::getCode()
{
	return code;
}

vector<ExceptionTableEntry>& CodeAttribute::getExceptionTable()
{
	return exceptionTable;
}
/**
 * 得到指定名称的属性
 * @param name
 * @return 返回AttributeInfo,如果找不到则 返回nullptr
 */
AttributeInfo* CodeAttribute::getAttribute(string name)
{
	for (auto & attribute : attributes)
	{
		if (attribute->getAttributeName() == name) return attribute;
	}
	return nullptr;
}