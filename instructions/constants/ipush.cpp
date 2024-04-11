#include"ipush.h"
void BIPUSH::fetchOperands(BytecodeReader* reader) {
    val = reader->readInt8();
}
void BIPUSH::execute(Frame* frame) {
    frame->operandStack.pushInt((int) val);
}


void SIPUSH::fetchOperands(BytecodeReader* reader) {
    val = reader->readInt16();
}
void SIPUSH::execute(Frame* frame) {
    frame->operandStack.pushInt((int) val);
}
