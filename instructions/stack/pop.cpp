#include"pop.h"
void POP::fetchOperands(BytecodeReader* reader) {

}
void POP::execute(Frame* frame) {
    frame->operandStack.popSlot();
}

void POP2::fetchOperands(BytecodeReader* reader) {

}
void POP2::execute(Frame* frame) {
    frame->operandStack.popSlot();
    frame->operandStack.popSlot();
}

