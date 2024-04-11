#pragma once
#include"../base/instruction.h"

//wideָ����õ���̬������������Ҫʹ�ü̳�
class ISTORE :public Instruction
{
private:
	unsigned int index;	//�ֲ������������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class LSTORE :public Instruction
{
private:
	unsigned int index;	//�ֲ������������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class FSTORE :public Instruction
{
private:
	unsigned int index;	//�ֲ������������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class DSTORE :public Instruction
{
private:
	unsigned int index;	//�ֲ������������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class ASTORE :public Instruction
{
private:
	unsigned int index;	//�ֲ������������
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class ISTORE_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ISTORE_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ISTORE_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ISTORE_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class LSTORE_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LSTORE_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LSTORE_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class LSTORE_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class FSTORE_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FSTORE_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FSTORE_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class FSTORE_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class DSTORE_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DSTORE_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DSTORE_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class DSTORE_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

class ASTORE_0 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ASTORE_1 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ASTORE_2 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
class ASTORE_3 :public Instruction
{
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};

