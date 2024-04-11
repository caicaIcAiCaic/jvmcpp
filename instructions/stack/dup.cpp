#include"dup.h"
void DUP::fetchOperands(BytecodeReader* reader) {

}
void DUP::execute(Frame* frame) {
    slot _slot = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(_slot);
    frame->operandStack.pushSlot(_slot);
}


void DUP_X1::fetchOperands(BytecodeReader* reader) {

}
void DUP_X1::execute(Frame* frame) {
    slot _slot_1 = frame->operandStack.popSlot();
    slot _slot_2 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(_slot_1);
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
}

void DUP_X2::fetchOperands(BytecodeReader* reader) {

}
void DUP_X2::execute(Frame* frame) {
    slot _slot_1 = frame->operandStack.popSlot();
    slot _slot_2 = frame->operandStack.popSlot();
    slot _slot_3 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(_slot_1);
    frame->operandStack.pushSlot(_slot_3);
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
}

void DUP2::fetchOperands(BytecodeReader* reader) {

}
void DUP2::execute(Frame* frame) {
    slot _slot_1 = frame->operandStack.popSlot();
    slot _slot_2 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
}

void DUP2_X1::fetchOperands(BytecodeReader* reader) {

}
void DUP2_X1::execute(Frame* frame) {
    slot _slot_1 = frame->operandStack.popSlot();
    slot _slot_2 = frame->operandStack.popSlot();
    slot _slot_3 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(_slot_1);
    frame->operandStack.pushSlot(_slot_3);
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
}

void DUP2_X2::fetchOperands(BytecodeReader* reader) {

}
void DUP2_X2::execute(Frame* frame) {
    slot _slot_1 = frame->operandStack.popSlot();
    slot _slot_2 = frame->operandStack.popSlot();
    slot _slot_3 = frame->operandStack.popSlot();
    slot _slot_4 = frame->operandStack.popSlot();

    frame->operandStack.pushSlot(_slot_1);
    frame->operandStack.pushSlot(_slot_4);
    frame->operandStack.pushSlot(_slot_3);
    frame->operandStack.pushSlot(_slot_2);
    frame->operandStack.pushSlot(_slot_1);
}
