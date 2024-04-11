#pragma once

const int ACC_PUBLIC = 0x0001;	// class field method
const int ACC_PRIVATE = 0x0002;	//       field method
const int ACC_PROTECTED = 0x0004;	//   field method
const int ACC_STATIC = 0x0008;	//       field method
const int ACC_FINAL = 0x0010;	// class field method
const int ACC_SUPER = 0x0020;	// 允许使用invoke_special字节码指令的新语义
const int ACC_SYNCHRONIZED = 0x0020;	//     method
const int ACC_VOLATILE = 0x0040;	//   field 字段为volatile
const int ACC_BRIDGE = 0x0040;	//             method 为编译器产生的桥接方法
const int ACC_TRANSIENT = 0x0080;	//   field 字段为transient
const int ACC_VARARGS = 0x0080;	//             method 方法接收不定参数
const int ACC_NATIVE = 0x0100;	//             method
const int ACC_INTERFACE = 0x0200;	//标识一个接口
const int ACC_ABSTRACT = 0x0400;	// class method
const int ACC_STRICT = 0x0800;	//             method 方法为strictfp
const int ACC_SYNTHETIC = 0x1000;	//类、字段、方法是由编译器自动产生的
const int ACC_ANNOTATION = 0x2000;
const int ACC_ENUM = 0x4000;


