#include"and.h"
void IAND::fetchOperands(BytecodeReader* reader) {

}
void IAND::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 & v2);
}

void LAND::fetchOperands(BytecodeReader* reader) {

}
void LAND::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 & v2);
}

void IOR::fetchOperands(BytecodeReader* reader) {

}
void IOR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 | v2);
}


void LOR::fetchOperands(BytecodeReader* reader) {

}
void LOR::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 | v2);
}

void IXOR::fetchOperands(BytecodeReader* reader) {

}
void IXOR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 ^ v2);
}

void LXOR::fetchOperands(BytecodeReader* reader) {

}
void LXOR::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 ^ v2);
}
