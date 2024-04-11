#pragma once
#include"..\..\rtda\frame.h"
#include"bytecode_reader.h"

//��JVM�ջ֡�еı��ر�����Ͳ�����ջֻ���������ݵ�ֵ��������¼��Ӧ����������
//�����Ľ������ÿ��ָ�����֪���Լ��ڲ���ʲô���͵�����

//��Ŀ¼ʵ��һ�����װ�����������е�ÿ��ָ�����ɽӿڣ������ִ���߼�ж�ؾ����ָ��ʵ����
class Instruction
{
public:
	virtual void fetchOperands(BytecodeReader* reader) = 0;	//���ֽ�������ȡ������
	virtual void execute(Frame* frame) = 0;		//ִ��ָ���߼�
	//virtual void setIndex(unsigned int _i) = 0;
	const char* toString();	//���ظ�ָ������֣��������֣�
};

////û�в�������ָ��
//class NoOperandsInstruction
//{
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//
//	}
//};
//
////��תָ��
//class BranchInstruction
//{
//private:
//	int offset;	//�����תƫ����
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		offset = int(reader->readInt16());	//���ֽ����ж�ȡ2�ֽ�����
//	}
//};
//
////�洢�ͼ�����Ҫ����������ȡ�ֲ�������
//class Index8Instruction
//{
//private:
//	unsigned int index;	//��ʾ�ֲ�����������
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		index = unsigned int(reader->readUint8());	//�޷���1�ֽ�����
//	}
//};
//
////��������ʱ�����أ�����ʾֲ�������ͬ�����Ĳ�������2�ֽ�
//class Index16Instruction
//{
//private:
//	unsigned int index;
//public:
//	void fetchOperands(BytecodeReader* reader)
//	{
//		index = unsigned int(reader->readUint16());
//	}
//};

