#include "jvm.h"
#include "instructions/base/base_logic.h"
#include"native/registry.h"

JVM::JVM(cmd* c) :myCmd(c)
{
	cp = new ClassPath(myCmd->getJreOption(), myCmd->getCpOption());
	loader = new ClassLoader(cp, myCmd->getVerboseClassFlag());
	mainThread = new Thread();
	interpreter = new Interpreter(myCmd->getVerboseInstFlag());
}

JVM::~JVM()
{
	delete interpreter;
	delete mainThread;
	delete loader;
	delete cp;
}

void JVM::start()
{
	initJVM();
	execMain();
}

void JVM::initJVM()
{
	REGISTRY::init();
}

void JVM::execMain()
{
	string className = myCmd->getClassName();
	Class* mainClass = loader->loadClass(className);
	Method* mainMethod = mainClass->getMainMethod();

	if (mainMethod == nullptr)
	{
		cout << "Main Method not found in class：" << className << endl;
		return;
	}

	Object* argsArr = createArgsArray();
	Frame* frame = new Frame(mainMethod, mainThread);
	frame->localVariablesTable.setRef(0, argsArr);	//将main方法传递参数args
	mainThread->pushFrame(frame);
	interpreter->interpret(mainThread);
}

Object* JVM::createArgsArray()
{
	vector<string>& args = myCmd->getArgs();
	Class* stringClass = loader->loadClass("java/lang/String");

	//字符串数组
	Object* argsArr = stringClass->getArrayClass()->newArray(args.size());
	//数组元素：String类型
	Object** jArgs = argsArr->getObjects();
	for (int i = 0; i < args.size(); i++)
	{
		jArgs[i] = StringPool::JString(loader, args[i]);
	}
	return argsArr;
}
