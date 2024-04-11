#include"x2x.h"
void D2I::fetchOperands(BytecodeReader* reader) {

}
void D2I::execute(Frame* frame) {
    double val = frame->operandStack.popDouble();
    frame->operandStack.pushInt((int) val);
}

void D2L::fetchOperands(BytecodeReader* reader) {

}
void D2L::execute(Frame* frame) {
    double val = frame->operandStack.popDouble();
    frame->operandStack.pushLong((long long) val);
}

void D2F::fetchOperands(BytecodeReader* reader) {

}
void D2F::execute(Frame* frame) {
    double val = frame->operandStack.popDouble();
    frame->operandStack.pushFloat((float) val);
}

void I2L::fetchOperands(BytecodeReader* reader) {

}
void I2L::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushLong((long long) val);
}

void I2F::fetchOperands(BytecodeReader* reader) {

}
void I2F::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushFloat((float) val);
}

void I2D::fetchOperands(BytecodeReader* reader) {

}
void I2D::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushDouble((double) val);
}

void L2I::fetchOperands(BytecodeReader* reader) {

}
void L2I::execute(Frame* frame) {
    long long val = frame->operandStack.popLong();
    frame->operandStack.pushInt((int) val);
}

void L2F::fetchOperands(BytecodeReader* reader) {

}
void L2F::execute(Frame* frame) {
    long long val = frame->operandStack.popLong();
    frame->operandStack.pushFloat((float) val);
}

void L2D::fetchOperands(BytecodeReader* reader) {

}
void L2D::execute(Frame* frame) {
    long long val = frame->operandStack.popLong();
    frame->operandStack.pushDouble((double) val);
}

void F2I::fetchOperands(BytecodeReader* reader) {

}
void F2I::execute(Frame* frame) {
    float val = frame->operandStack.popFloat();
    frame->operandStack.pushInt((int) val);
}

void F2L::fetchOperands(BytecodeReader* reader) {

}
void F2L::execute(Frame* frame) {
    float val = frame->operandStack.popFloat();
    frame->operandStack.pushLong((long long) val);
}

void F2D::fetchOperands(BytecodeReader* reader) {

}
void F2D::execute(Frame* frame) {
    float val = frame->operandStack.popFloat();
    frame->operandStack.pushDouble((double) val);
}

void I2B::fetchOperands(BytecodeReader* reader) {

}
void I2B::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushInt((unsigned char) val);
}

void I2C::fetchOperands(BytecodeReader* reader) {

}
void I2C::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushInt((char) val);
}

void I2S::fetchOperands(BytecodeReader* reader) {

}
void I2S::execute(Frame* frame) {
    int val = frame->operandStack.popInt();
    frame->operandStack.pushInt((short) val);
}
