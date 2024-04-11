#pragma once
#include"../base/instruction.h"

class ClassLoader;

//newarray���ڴ������������������飺bool[] byte[] char[] short[] int[] long[] float[] double[]
//��һ��������ռ1�ֽڣ����ڲ�������棬��ʾ����ʲô���͵�����
//�ڶ���������ռcount���Ӳ�����ջ�е���
class NEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//1�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);	
	void execute(Frame* frame);		
private:
	Class* getPrimitiveArrayClass(ClassLoader* loader, unsigned int atype);
};


//anewarrayָ�����ڴ���������������
//��һ��������ָ������ʱ�����ص�һ�����������
//�ڶ��������������鳤�ȣ��Ӳ�����ջ�е���
class ANEW_ARRAY :public Instruction
{
private:
	unsigned int index;	//2�ֽ�
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
private:
	
};


//arraylengthָ�����ڻ�ȡ���鳤��
class ARRAY_LENGTH :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
