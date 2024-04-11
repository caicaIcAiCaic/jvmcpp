#include"swap.h"


void SWAP::fetchOperands(BytecodeReader* reader)
{

}
void SWAP::execute(Frame* frame)
{
	slot _slot_1 = frame->operandStack.popSlot();
	slot _slot_2 = frame->operandStack.popSlot();
	frame->operandStack.pushSlot(_slot_1);
	frame->operandStack.pushSlot(_slot_2);
}


