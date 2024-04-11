#include"cmp.h"
void LCMP::fetchOperands(BytecodeReader* reader) {

}
void LCMP::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    if (v1 > v2) {
        frame->operandStack.pushInt(1);
    } else if (v1 == v2) {
        frame->operandStack.pushInt(0);
    } else {
        frame->operandStack.pushInt(-1);
    }

}

void FCMPL::fetchOperands(BytecodeReader* reader) {

}
void FCMPL::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    if (v1 > v2) {
        frame->operandStack.pushInt(1);
    } else if (v1 == v2) {
        frame->operandStack.pushInt(0);
    } else {
        frame->operandStack.pushInt(-1);
    }
}


void FCMPG::fetchOperands(BytecodeReader* reader) {

}
void FCMPG::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    if (v1 < v2) {
        frame->operandStack.pushInt(-1);
    } else if (v1 == v2) {
        frame->operandStack.pushInt(0);
    } else {
        frame->operandStack.pushInt(1);
    }
}

void DCMPL::fetchOperands(BytecodeReader* reader) {

}
void DCMPL::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    if (v1 > v2) {
        frame->operandStack.pushInt(1);
    } else if (v1 == v2) {
        frame->operandStack.pushInt(0);
    } else {
        frame->operandStack.pushInt(-1);
    }
}

void DCMPG::fetchOperands(BytecodeReader* reader) {

}
void DCMPG::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    if (v1 < v2) {
        frame->operandStack.pushInt(-1);
    } else if (v1 == v2) {
        frame->operandStack.pushInt(0);
    } else {
        frame->operandStack.pushInt(1);
    }
}
