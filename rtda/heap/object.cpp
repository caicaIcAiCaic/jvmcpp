#include"object.h"
#include"../../rtda/heap/class.h"

Object::Object(Class* c, void* s, unsigned int al):_class(c),extra(nullptr),data(s),arraylength(al)
{

}
//Object::~Object()
//{
//	delete[] data;
//}


Class* Object::getClass()
{
	return _class;
}
void* Object::getExtra()
{
	return extra;
}
void Object::setExtra(void* e)
{
	extra = e;
}

Slots* Object::getFields()
{
    return static_cast<Slots*>(data);
}
char* Object::getBytes()
{
	return (char*)data;
}
short* Object::getShorts()
{
	return (short*)data;
}
int* Object::getInts()
{
	return (int*)data;
}
long long* Object::getLongs()
{
	return (long long*)data;
}
wchar_t* Object::getChars()
{
	return (wchar_t*)data;
}
float* Object::getFloats()
{
	return (float*)data;
}
double* Object::getDoubles()
{
	return (double*)data;
}
Object** Object::getObjects()
{
	return (Object**)data;
}

unsigned int Object::getArrayLength()
{
	return arraylength;
}

void Object::SetRefVar(string name, string descriptor, Object* ref)
{
	Field* f = _class->getField(name, descriptor, false);
	Slots* slots = (Slots*)data;
	slots->setRef(f->getSlotId(), ref);
}
Object* Object::GetRefVar(string name, string descriptor)
{
	Field* f = _class->getField(name, descriptor,false);
	Slots* slots = (Slots*)data;
	return slots->getRef(f->getSlotId());
}

bool Object::IsInstanceOf(Class* c)
{
	return c->isAssignableFrom(_class);
}
Object* Object::Clone()
{
	if (_class->isArray())	//是数组类
	{
		string type = _class->getComponentClassName();
		if (type == "boolean")
		{
			char* elements = (char*)data;
			char* elements2 = new char[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "byte")
		{
			char* elements = (char*)data;
			char* elements2 = new char[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "char")
		{
			wchar_t* elements = (wchar_t*)data;
			wchar_t* elements2 = new wchar_t[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "short")
		{
			short* elements = (short*)data;
			short* elements2 = new short[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "int")
		{
			int* elements = (int*)data;
			int* elements2 = new int[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "long")
		{
			long long* elements = (long long*)data;
			long long* elements2 = new long long[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "float")
		{
			float* elements = (float*)data;
			float* elements2 = new float[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else if (type == "double")
		{
			double* elements = (double*)data;
			double* elements2 = new double[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
		else
		{	//引用数据类型
			Object** elements = (Object**)data;
			Object** elements2 = new Object*[arraylength];
			for (int i = 0; i < arraylength; i++) elements2[i] = elements[i];

			Object* obj = new Object(_class, elements2, arraylength);
			obj->setExtra(extra);
			return obj;
		}
	}
	//普通数据类型，data中的数据是slot
	Slots* slot = (Slots*)data;
	Slots* slot2 = new Slots(*slot);	//使用赋值构造函数,浅复制即可
	Object* obj = new Object(_class, slot2, arraylength);
	obj->setExtra(extra);
	return obj;
}

void Object::ArrayCopy(Object* src, Object* dst, int srcPos, int dstPos, int length)
{
	string type = src->getClass()->getComponentClassName();
	if (type == "boolean")
	{
		char* _src = src->getBytes();
		char* _dst = dst->getBytes();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "byte")
	{
		char* _src = src->getBytes();
		char* _dst = dst->getBytes();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "char")
	{
		wchar_t* _src = src->getChars();
		wchar_t* _dst = dst->getChars();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "short")
	{
		short* _src = src->getShorts();
		short* _dst = dst->getShorts();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "int")
	{
		int* _src = src->getInts();
		int* _dst = dst->getInts();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "long")
	{
		long long* _src = src->getLongs();
		long long* _dst = dst->getLongs();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "float")
	{
		float* _src = src->getFloats();
		float* _dst = dst->getFloats();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else if (type == "double")
	{
		double* _src = src->getDoubles();
		double* _dst = dst->getDoubles();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
	else
	{	//引用数据类型
		Object** _src = src->getObjects();
		Object** _dst = dst->getObjects();
		for (int i = 0; i < length; i++) _dst[dstPos + i] = _src[srcPos + i];
	}
}
