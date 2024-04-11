#include"athrow.h"
#include"../../rtda/thread.h"
#include"../../rtda/heap/string_pool.h"
#include"../../native/java/lang/Throwable0.h"

void ATHROW::fetchOperands(BytecodeReader* reader)
{

}

void ATHROW::execute(Frame* frame)
{
	Object* ex = frame->operandStack.popRef();
	if (ex == nullptr)
	{
		cout << "java.lang.NullPointerException" << endl;
		exit(0);
	}

	Thread* t = frame->thread;
	if (!findAndGotoExceptionHandler(t, ex)) handleUncaughtException(t, ex);
}

bool ATHROW::findAndGotoExceptionHandler(Thread* t, Object* ex)
{
	//遍历当前Java虚拟机栈，查找方法的异常处理表
	while (true)
	{
		Frame* f = t->CurrentFrame();
		int pc = f->getNextPC() - 1;	//athrow指令没有操作数，只占一个字节，这里-1返回上一条指令

		int handlerPC = f->method->findExceptionHandler(ex->getClass(), pc);
		if (handlerPC > 0)
		{
			//如果找到了异常处理项，再跳转到异常处理代码之前，要先把F的操作数栈清空，然后将异常对象引用推入栈顶
			OperandStack& stack = f->operandStack;
			stack.Clear();
			stack.pushRef(ex);
			f->setNextPC(handlerPC);
			return true;
		}

		t->popFrame();
		if (t->isStackEmpty()) break;
	}
	return false;
}

void ATHROW::handleUncaughtException(Thread* t, Object* ex)
{
	t->ClearStack();

	Object* jMsg = ex->GetRefVar("detailMessage", "Ljava/lang/String;");
	string cppMsg = StringPool::cppString(jMsg);
	cout << ex->getClass()->JavaName() << ": " << cppMsg << endl;

	StackTraceElement* stes = (StackTraceElement*)ex->getExtra();
	int len = stes[0].lineNumber;
	for (int i = 1; i < len; i++)
	{
		cout << "\tat " << stes[i].className << "." << stes[i].methodName << "(" << stes[i].fileName << ":"
			<< stes[i].lineNumber << ")" << endl;
	}
}
