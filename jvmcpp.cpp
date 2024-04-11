// jvmcpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"jvm.h"
void Myjavap(vector<unsigned char>& bytes);

int main(int argc, char* argv[])
{
     cmd myCmd = cmd(R"(D:\Java\jdk8\jre)", R"(F:\Something\jvmt)", "GaussTest");
//    cmd myCmd = cmd(argc, argv);
    if (myCmd.getVersionFlag()) {
        cout << "java version 1.8.0_281 2020-10-20" << endl;
    }
    else if (myCmd.getClassName().empty()) {
        myCmd.printUsage();
    }
    else {
        (new JVM(&myCmd))->start();
    }
}

void Myjavap(vector<unsigned char>& bytes)
{
    ClassReader reader(bytes);
    ClassFile file(reader);
    cout << "version:" << std::dec << file.getMajorVersion() << "." << file.getMinorVersion() << endl;
    cout << "constant count:" << file.getConstantPool()->getConstantPoolCount() << endl;
    cout << "access flags:" << file.getAccessFlags() << endl;
    cout << "this class:" << file.getConstantPool()->getClssName(file.getThisClass()) << endl;
    cout << "super class:" << file.getConstantPool()->getClssName(file.getSuperClass()) << endl;
    cout << "interface count:" << file.getInterfaceCount() << endl;
    cout << "interfaces:" << endl;
    for (u2 i = 0; i < file.getInterfaceCount(); i++)
    {
        cout << "   " << file.getConstantPool()->getClssName(file.getInterfaces()[i]) << endl;
    }
    cout << "field count:" << file.getFieldCount() << endl;
    cout << "fields:" << endl;
    for (u2 i = 0; i < file.getFieldCount(); i++)
    {
        cout << "   " << file.getFields()[i]->getName() << endl;
    }
    cout << "method count:" << file.getMethodCount() << endl;
    cout << "methods:" << endl;
    for (u2 i = 0; i < file.getMethodCount(); i++)
    {
        cout << "   " << file.getMethods()[i]->getName() << endl;
    }
}

