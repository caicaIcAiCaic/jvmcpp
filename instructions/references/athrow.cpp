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
	//������ǰJava�����ջ�����ҷ������쳣�����
	while (true)
	{
		Frame* f = t->CurrentFrame();
		int pc = f->getNextPC() - 1;	//athrowָ��û�в�������ֻռһ���ֽڣ�����-1������һ��ָ��

		int handlerPC = f->method->findExceptionHandler(ex->getClass(), pc);
		if (handlerPC > 0)
		{
			//����ҵ����쳣���������ת���쳣�������֮ǰ��Ҫ�Ȱ�F�Ĳ�����ջ��գ�Ȼ���쳣������������ջ��
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
