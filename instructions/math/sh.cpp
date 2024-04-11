#include"sh.h"
void ISHL::fetchOperands(BytecodeReader* reader) {

}
void ISHL::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    unsigned int _v2 = (unsigned int) v2 & 0x1f;    //int 变量只有32位，所以只取前5个比特就足够表示位移位数了
    frame->operandStack.pushInt(v1 << _v2);
}

void ISHR::fetchOperands(BytecodeReader* reader) {

}
void ISHR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    unsigned int _v2 = (unsigned int) v2 & 0x1f;
    frame->operandStack.pushInt(v1 >> _v2);
}

void IUSHR::fetchOperands(BytecodeReader* reader) {

}
void IUSHR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    unsigned int _v2 = (unsigned int) v2 & 0x1f;
    unsigned int _v1 = (unsigned int) v1 >> _v2;
    frame->operandStack.pushInt((int) _v1);
}

void LSHL::fetchOperands(BytecodeReader* reader) {

}
void LSHL::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    long long v1 = frame->operandStack.popLong();
    unsigned int _v2 = (unsigned int) v2 & 0x3f;
    frame->operandStack.pushLong(v1 << _v2);
}

void LSHR::fetchOperands(BytecodeReader* reader) {

}
void LSHR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    long long v1 = frame->operandStack.popLong();
    unsigned int _v2 = (unsigned int) v2 & 0x3f;    //long long有64位，取前6个比特
    frame->operandStack.pushLong(v1 >> _v2);
}

void LUSHR::fetchOperands(BytecodeReader* reader) {

}
void LUSHR::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    long long v1 = frame->operandStack.popLong();
    unsigned int _v2 = (unsigned int) v2 & 0x3f;
    unsigned long long _v1 = (unsigned long long) v1 >> _v2;
    frame->operandStack.pushLong((long long) _v1);
}
