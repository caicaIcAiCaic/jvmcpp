#pragma once
#include"../base/instruction.h"

//用于调用接口方法，会在运行时再确定一个实现该接口的对象
//invoke_interface指令的操作码后面跟着4字节而非2字节
//前2个字节的含义与其他函数调用指令相同，指向了运行时常量池的一个发给发引用
//第3个字节的值是再给方法传递参数需要的slot数，其含义与Method结构体中定义的argSlotCount字段相同
//我们知道这个数值是可以根据方法的描述符计算出来的，它的存在仅仅是因为历史原因
//第4个字节是留给Oracle的某些Java虚拟机实现用的，它的值必须是0。该字节的存在保证了Java虚拟机向后兼容
class INVOKE_INTERFACE :public Instruction
{
	//hack!
private:
	unsigned int index;	//4字节
	unsigned int argSlotCount;
public:
	void fetchOperands(BytecodeReader* reader);
	void execute(Frame* frame);
};
