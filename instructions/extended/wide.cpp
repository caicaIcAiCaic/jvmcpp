#include"wide.h"
#include"..\loads\load.h"
#include"..\stores\store.h"
#include"..\math\iinc.h"
#include <iostream>

//wide指令需要自己解码出modifiedInstruction
void WIDE::fetchOperands(BytecodeReader* reader)
{
	int opcode = reader->readUint8();
	switch (opcode)
	{
	case 0x15:	//iload
		inst = new ILOAD();
		((ILOAD*)inst)->setIndex(reader->readUint16());
		break;
	case 0x16:	//load
		inst = new LLOAD();
		((LLOAD*)inst)->setIndex(reader->readUint16());
		break;
	case 0x17:	//fload
		inst = new FLOAD();
		((FLOAD*)inst)->setIndex(reader->readUint16());
		break;
	case 0x18:	//dload
		inst = new DLOAD();
		((DLOAD*)inst)->setIndex(reader->readUint16());
		break;
	case 0x19:	//aload
		inst = new ALOAD();
		((ALOAD*)inst)->setIndex(reader->readUint16());
		break;
	case 0x36:	//istore
		inst = new ISTORE();
		((ISTORE*)inst)->setIndex(reader->readUint16());
		break;
	case 0x37:	//lstore
		inst = new LSTORE();
		((LSTORE*)inst)->setIndex(reader->readUint16());
		break;
	case 0x38:	//fstore
		inst = new FSTORE();
		((FSTORE*)inst)->setIndex(reader->readUint16());
		break;
	case 0x39:	//dstore
		inst = new DSTORE();
		((DSTORE*)inst)->setIndex(reader->readUint16());
		break;
	case 0x3a:	//astore
		inst = new ASTORE();
		((ASTORE*)inst)->setIndex(reader->readUint16());
		break;
	case 0x84:	//iinc
		inst = new IINC();
		((IINC*)inst)->setIndex(reader->readUint16());
		((IINC*)inst)->setConst(reader->readInt16());
		break;
	case 0xa9:	//ret
		std::cout << "Unsupported opcode: 0xa9!" << std::endl;
		exit(0);
	}
}
void WIDE::execute(Frame* frame)
{
	inst->execute(frame);
}

WIDE::~WIDE()
{
	delete inst;
}
