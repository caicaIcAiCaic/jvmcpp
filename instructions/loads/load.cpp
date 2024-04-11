#include"load.h"
void ILOAD::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void ILOAD::execute(Frame* frame) {
    frame->operandStack.pushInt(frame->localVariablesTable.getInt(index));
}
void ILOAD::setIndex(unsigned int _i) {
    index = _i;
}


void LLOAD::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void LLOAD::execute(Frame* frame) {
    frame->operandStack.pushLong(frame->localVariablesTable.getLong(index));
}
void LLOAD::setIndex(unsigned int _i) {
    index = _i;
}


void FLOAD::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void FLOAD::execute(Frame* frame) {
    frame->operandStack.pushFloat(frame->localVariablesTable.getFloat(index));
}
void FLOAD::setIndex(unsigned int _i) {
    index = _i;
}

void DLOAD::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void DLOAD::execute(Frame* frame) {
    frame->operandStack.pushDouble(frame->localVariablesTable.getDouble(index));
}
void DLOAD::setIndex(unsigned int _i) {
    index = _i;
}

void ALOAD::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void ALOAD::execute(Frame* frame) {
    frame->operandStack.pushRef(frame->localVariablesTable.getRef(index));
}
void ALOAD::setIndex(unsigned int _i) {
    index = _i;
}

void ILOAD_0::fetchOperands(BytecodeReader* reader) {

}
void ILOAD_0::execute(Frame* frame) {
    frame->operandStack.pushInt(frame->localVariablesTable.getInt(0));
}


void ILOAD_1::fetchOperands(BytecodeReader* reader) {

}
void ILOAD_1::execute(Frame* frame) {
    frame->operandStack.pushInt(frame->localVariablesTable.getInt(1));
}

void ILOAD_2::fetchOperands(BytecodeReader* reader) {

}
void ILOAD_2::execute(Frame* frame) {
    frame->operandStack.pushInt(frame->localVariablesTable.getInt(2));
}

void ILOAD_3::fetchOperands(BytecodeReader* reader) {

}
void ILOAD_3::execute(Frame* frame) {
    frame->operandStack.pushInt(frame->localVariablesTable.getInt(3));
}

void LLOAD_0::fetchOperands(BytecodeReader* reader) {

}
void LLOAD_0::execute(Frame* frame) {
    frame->operandStack.pushLong(frame->localVariablesTable.getLong(0));
}


void LLOAD_1::fetchOperands(BytecodeReader* reader) {

}
void LLOAD_1::execute(Frame* frame) {
    frame->operandStack.pushLong(frame->localVariablesTable.getLong(1));
}

void LLOAD_2::fetchOperands(BytecodeReader* reader) {

}
void LLOAD_2::execute(Frame* frame) {
    frame->operandStack.pushLong(frame->localVariablesTable.getLong(2));
}

void LLOAD_3::fetchOperands(BytecodeReader* reader) {

}
void LLOAD_3::execute(Frame* frame) {
    frame->operandStack.pushLong(frame->localVariablesTable.getLong(3));
}

void FLOAD_0::fetchOperands(BytecodeReader* reader) {

}
void FLOAD_0::execute(Frame* frame) {
    frame->operandStack.pushFloat(frame->localVariablesTable.getFloat(0));
}

void FLOAD_1::fetchOperands(BytecodeReader* reader) {

}
void FLOAD_1::execute(Frame* frame) {
    frame->operandStack.pushFloat(frame->localVariablesTable.getFloat(1));
}

void FLOAD_2::fetchOperands(BytecodeReader* reader) {

}
void FLOAD_2::execute(Frame* frame) {
    frame->operandStack.pushFloat(frame->localVariablesTable.getFloat(2));
}

void FLOAD_3::fetchOperands(BytecodeReader* reader) {

}
void FLOAD_3::execute(Frame* frame) {
    frame->operandStack.pushFloat(frame->localVariablesTable.getFloat(3));
}

void DLOAD_0::fetchOperands(BytecodeReader* reader) {

}
void DLOAD_0::execute(Frame* frame) {
    frame->operandStack.pushDouble(frame->localVariablesTable.getDouble(0));
}

void DLOAD_1::fetchOperands(BytecodeReader* reader) {

}
void DLOAD_1::execute(Frame* frame) {
    frame->operandStack.pushDouble(frame->localVariablesTable.getDouble(1));
}

void DLOAD_2::fetchOperands(BytecodeReader* reader) {

}
void DLOAD_2::execute(Frame* frame) {
    frame->operandStack.pushDouble(frame->localVariablesTable.getDouble(2));
}

void DLOAD_3::fetchOperands(BytecodeReader* reader) {

}
void DLOAD_3::execute(Frame* frame) {
    frame->operandStack.pushDouble(frame->localVariablesTable.getDouble(3));
}

void ALOAD_0::fetchOperands(BytecodeReader* reader) {

}
void ALOAD_0::execute(Frame* frame) {
    frame->operandStack.pushRef(frame->localVariablesTable.getRef(0));
}

void ALOAD_1::fetchOperands(BytecodeReader* reader) {

}
void ALOAD_1::execute(Frame* frame) {
    frame->operandStack.pushRef(frame->localVariablesTable.getRef(1));
}

void ALOAD_2::fetchOperands(BytecodeReader* reader) {

}
void ALOAD_2::execute(Frame* frame) {
    frame->operandStack.pushRef(frame->localVariablesTable.getRef(2));
}

void ALOAD_3::fetchOperands(BytecodeReader* reader) {

}
void ALOAD_3::execute(Frame* frame) {
    frame->operandStack.pushRef(frame->localVariablesTable.getRef(3));
}