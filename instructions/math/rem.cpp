#include"rem.h"
void IREM::fetchOperands(BytecodeReader* reader) {

}
void IREM::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    if (v2 == 0) {
        std::cout << "java.lang.ArithmeticException: / by zero" << std::endl;
        exit(0);
    }
    frame->operandStack.pushInt(v1 % v2);
}

void LREM::fetchOperands(BytecodeReader* reader) {

}
void LREM::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    if (v2 == 0) {
        std::cout << "java.lang.ArithmeticException: / by zero" << std::endl;
        exit(0);
    }
    frame->operandStack.pushLong(v1 % v2);
}

void DREM::fetchOperands(BytecodeReader* reader) {

}
void DREM::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    if (v2 == 0)
        frame->operandStack.pushDouble(fmod(v1, v2));
}

void FREM::fetchOperands(BytecodeReader* reader) {

}
void FREM::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(fmod(v1, v2));
}

void IADD::fetchOperands(BytecodeReader* reader) {

}
void IADD::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 + v2);
}

void LADD::fetchOperands(BytecodeReader* reader) {

}
void LADD::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 + v2);
}

void FADD::fetchOperands(BytecodeReader* reader) {

}
void FADD::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1 + v2);
}

void DADD::fetchOperands(BytecodeReader* reader) {

}
void DADD::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1 + v2);
}

void ISUB::fetchOperands(BytecodeReader* reader) {

}
void ISUB::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 - v2);
}

void LSUB::fetchOperands(BytecodeReader* reader) {

}
void LSUB::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 - v2);
}

void FSUB::fetchOperands(BytecodeReader* reader) {

}
void FSUB::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1 - v2);
}

void DSUB::fetchOperands(BytecodeReader* reader) {

}
void DSUB::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1 - v2);
}

void IMUL::fetchOperands(BytecodeReader* reader) {

}
void IMUL::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 * v2);
}


void LMUL::fetchOperands(BytecodeReader* reader) {

}
void LMUL::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 * v2);
}


void FMUL::fetchOperands(BytecodeReader* reader) {

}
void FMUL::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1 * v2);
}

void DMUL::fetchOperands(BytecodeReader* reader) {

}
void DMUL::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1 * v2);
}

void IDIV::fetchOperands(BytecodeReader* reader) {

}
void IDIV::execute(Frame* frame) {
    int v2 = frame->operandStack.popInt();
    int v1 = frame->operandStack.popInt();
    if (v2 == 0) {
        std::cout << "java.lang.ArithmeticException: / by zero" << std::endl;
        exit(0);
    }
    frame->operandStack.pushInt(v1 / v2);
}

void LDIV::fetchOperands(BytecodeReader* reader) {

}
void LDIV::execute(Frame* frame) {
    long long v2 = frame->operandStack.popLong();
    long long v1 = frame->operandStack.popLong();
    if (v2 == 0) {
        std::cout << "java.lang.ArithmeticException: / by zero" << std::endl;
        exit(0);
    }
    frame->operandStack.pushLong(v1 / v2);
}

void FDIV::fetchOperands(BytecodeReader* reader) {

}
void FDIV::execute(Frame* frame) {
    float v2 = frame->operandStack.popFloat();
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1 / v2);
}

void DDIV::fetchOperands(BytecodeReader* reader) {

}
void DDIV::execute(Frame* frame) {
    double v2 = frame->operandStack.popDouble();
    double v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1 / v2);
}

void INEG::fetchOperands(BytecodeReader* reader) {

}
void INEG::execute(Frame* frame) {
    int v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(-v1);
}

void LNEG::fetchOperands(BytecodeReader* reader) {

}
void LNEG::execute(Frame* frame) {
    long long v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(-v1);
}

void FNEG::fetchOperands(BytecodeReader* reader) {

}
void FNEG::execute(Frame* frame) {
    float v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(-v1);
}


void DNEG::fetchOperands(BytecodeReader* reader) {

}
void DNEG::execute(Frame* frame) {
    double v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(-v1);
}
