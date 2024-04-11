#pragma once

#include"..\base\instruction.h"

//�����wideָ��Ҫʹ�ö�̬�����Ա���ʹ�ü̳�
class ILOAD:public Instruction
{
private:
	unsigned int index;	//�ֲ�����������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class LLOAD :public Instruction
{
private:
	unsigned int index;	//�ֲ�����������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class FLOAD :public Instruction
{
private:
	unsigned int index;	//�ֲ�����������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class DLOAD :public Instruction
{
private:
	unsigned int index;	//�ֲ�����������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class ALOAD :public Instruction
{
private:
	unsigned int index;	//�ֲ�����������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class ILOAD_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);

};
class ILOAD_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ILOAD_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ILOAD_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class LLOAD_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LLOAD_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LLOAD_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LLOAD_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class FLOAD_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FLOAD_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FLOAD_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FLOAD_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class DLOAD_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DLOAD_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DLOAD_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DLOAD_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class ALOAD_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ALOAD_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ALOAD_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ALOAD_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};







