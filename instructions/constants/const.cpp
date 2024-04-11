#include"const.h"
void ACONST_NULL::fetchOperands(BytecodeReader* reader) {

}
void ACONST_NULL::execute(Frame* frame) {
    frame->operandStack.pushRef(NULL);
}

void DCONST_0::fetchOperands(BytecodeReader* reader) {

}
void DCONST_0::execute(Frame* frame) {
    frame->operandStack.pushDouble(0.0);
}

void DCONST_1::fetchOperands(BytecodeReader* reader) {

}
void DCONST_1::execute(Frame* frame) {
    frame->operandStack.pushDouble(1.0);
}

void FCONST_0::fetchOperands(BytecodeReader* reader) {

}
void FCONST_0::execute(Frame* frame) {
    frame->operandStack.pushFloat(0.0);
}

void FCONST_1::fetchOperands(BytecodeReader* reader) {

}
void FCONST_1::execute(Frame* frame) {
    frame->operandStack.pushFloat(1.0);
}

void FCONST_2::fetchOperands(BytecodeReader* reader) {

}
void FCONST_2::execute(Frame* frame) {
    frame->operandStack.pushFloat(2.0);
}

void ICONST_M1::fetchOperands(BytecodeReader* reader) {

}
void ICONST_M1::execute(Frame* frame) {
    frame->operandStack.pushInt(-1);
}

void ICONST_0::fetchOperands(BytecodeReader* reader) {

}
void ICONST_0::execute(Frame* frame) {
    frame->operandStack.pushInt(0);
}

void ICONST_1::fetchOperands(BytecodeReader* reader) {

}
void ICONST_1::execute(Frame* frame) {
    frame->operandStack.pushInt(1);
}

void ICONST_2::fetchOperands(BytecodeReader* reader) {

}
void ICONST_2::execute(Frame* frame) {
    frame->operandStack.pushInt(2);
}

void ICONST_3::fetchOperands(BytecodeReader* reader) {

}
void ICONST_3::execute(Frame* frame) {
    frame->operandStack.pushInt(3);
}

void ICONST_4::fetchOperands(BytecodeReader* reader) {

}
void ICONST_4::execute(Frame* frame) {
    frame->operandStack.pushInt(4);
}

void ICONST_5::fetchOperands(BytecodeReader* reader) {

}
void ICONST_5::execute(Frame* frame) {
    frame->operandStack.pushInt(5);
}

void LCONST_0::fetchOperands(BytecodeReader* reader) {

}
void LCONST_0::execute(Frame* frame) {
    frame->operandStack.pushLong(0);
}

void LCONST_1::fetchOperands(BytecodeReader* reader) {

}
void LCONST_1::execute(Frame* frame) {
    frame->operandStack.pushLong(1);
}
