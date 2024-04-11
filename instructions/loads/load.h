#pragma once

#include"..\base\instruction.h"

//后面的wide指令要使用多态，所以必须使用继承
class ILOAD:public Instruction
{
private:
	unsigned int index;	//局部变量表索引
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class LLOAD :public Instruction
{
private:
	unsigned int index;	//局部变量表索引
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class FLOAD :public Instruction
{
private:
	unsigned int index;	//局部变量表索引
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class DLOAD :public Instruction
{
private:
	unsigned int index;	//局部变量表索引
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
	void setIndex(unsigned int _i);
};

class ALOAD :public Instruction
{
private:
	unsigned int index;	//局部变量表索引
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







