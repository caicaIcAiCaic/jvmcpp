#include"store.h"
void ISTORE::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void ISTORE::execute(Frame* frame) {
    frame->localVariablesTable.setInt((unsigned int) index, frame->operandStack.popInt());
}
void ISTORE::setIndex(unsigned int _i) {
    index = _i;
}

void LSTORE::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void LSTORE::execute(Frame* frame) {
    frame->localVariablesTable.setLong((unsigned int) index, frame->operandStack.popLong());
}
void LSTORE::setIndex(unsigned int _i) {
    index = _i;
}


void FSTORE::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void FSTORE::execute(Frame* frame) {
    frame->localVariablesTable.setFloat((unsigned int) index, frame->operandStack.popFloat());
}
void FSTORE::setIndex(unsigned int _i) {
    index = _i;
}

void DSTORE::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void DSTORE::execute(Frame* frame) {
    frame->localVariablesTable.setDouble((unsigned int) index, frame->operandStack.popDouble());
}
void DSTORE::setIndex(unsigned int _i) {
    index = _i;
}

void ASTORE::fetchOperands(BytecodeReader* reader) {
    index = reader->readUint8();
}
void ASTORE::execute(Frame* frame) {
    frame->localVariablesTable.setRef((unsigned int) index, frame->operandStack.popRef());
}
void ASTORE::setIndex(unsigned int _i) {
    index = _i;
}

void ISTORE_0::fetchOperands(BytecodeReader* reader) {

}
void ISTORE_0::execute(Frame* frame) {
    frame->localVariablesTable.setInt(0, frame->operandStack.popInt());
}

void ISTORE_1::fetchOperands(BytecodeReader* reader) {

}
void ISTORE_1::execute(Frame* frame) {
    frame->localVariablesTable.setInt(1, frame->operandStack.popInt());
}

void ISTORE_2::fetchOperands(BytecodeReader* reader) {

}
void ISTORE_2::execute(Frame* frame) {
    frame->localVariablesTable.setInt(2, frame->operandStack.popInt());
}

void ISTORE_3::fetchOperands(BytecodeReader* reader) {

}
void ISTORE_3::execute(Frame* frame) {
    frame->localVariablesTable.setInt(3, frame->operandStack.popInt());
}

void LSTORE_0::fetchOperands(BytecodeReader* reader) {

}
void LSTORE_0::execute(Frame* frame) {
    frame->localVariablesTable.setLong(0, frame->operandStack.popLong());
}

void LSTORE_1::fetchOperands(BytecodeReader* reader) {

}
void LSTORE_1::execute(Frame* frame) {
    frame->localVariablesTable.setLong(1, frame->operandStack.popLong());
}

void LSTORE_2::fetchOperands(BytecodeReader* reader) {

}
void LSTORE_2::execute(Frame* frame) {
    frame->localVariablesTable.setLong(2, frame->operandStack.popLong());
}

void LSTORE_3::fetchOperands(BytecodeReader* reader) {

}
void LSTORE_3::execute(Frame* frame) {
    frame->localVariablesTable.setLong(3, frame->operandStack.popLong());
}

void FSTORE_0::fetchOperands(BytecodeReader* reader) {

}
void FSTORE_0::execute(Frame* frame) {
    frame->localVariablesTable.setFloat(0, frame->operandStack.popFloat());
}

void FSTORE_1::fetchOperands(BytecodeReader* reader) {

}
void FSTORE_1::execute(Frame* frame) {
    frame->localVariablesTable.setFloat(1, frame->operandStack.popFloat());
}

void FSTORE_2::fetchOperands(BytecodeReader* reader) {

}
void FSTORE_2::execute(Frame* frame) {
    frame->localVariablesTable.setFloat(2, frame->operandStack.popFloat());
}

void FSTORE_3::fetchOperands(BytecodeReader* reader) {

}
void FSTORE_3::execute(Frame* frame) {
    frame->localVariablesTable.setFloat(3, frame->operandStack.popFloat());
}

void DSTORE_0::fetchOperands(BytecodeReader* reader) {

}
void DSTORE_0::execute(Frame* frame) {
    frame->localVariablesTable.setDouble(0, frame->operandStack.popDouble());
}

void DSTORE_1::fetchOperands(BytecodeReader* reader) {

}
void DSTORE_1::execute(Frame* frame) {
    frame->localVariablesTable.setDouble(1, frame->operandStack.popDouble());
}

void DSTORE_2::fetchOperands(BytecodeReader* reader) {

}
void DSTORE_2::execute(Frame* frame) {
    frame->localVariablesTable.setDouble(2, frame->operandStack.popDouble());
}

void DSTORE_3::fetchOperands(BytecodeReader* reader) {

}
void DSTORE_3::execute(Frame* frame) {
    frame->localVariablesTable.setDouble(3, frame->operandStack.popDouble());
}

void ASTORE_0::fetchOperands(BytecodeReader* reader) {

}
void ASTORE_0::execute(Frame* frame) {
    frame->localVariablesTable.setRef(0, frame->operandStack.popRef());
}

void ASTORE_1::fetchOperands(BytecodeReader* reader) {

}
void ASTORE_1::execute(Frame* frame) {
    frame->localVariablesTable.setRef(1, frame->operandStack.popRef());
}

void ASTORE_2::fetchOperands(BytecodeReader* reader) {

}
void ASTORE_2::execute(Frame* frame) {
    frame->localVariablesTable.setRef(2, frame->operandStack.popRef());
}

void ASTORE_3::fetchOperands(BytecodeReader* reader) {

}
void ASTORE_3::execute(Frame* frame) {
    frame->localVariablesTable.setRef(3, frame->operandStack.popRef());
}
