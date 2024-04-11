#pragma once

const int ACC_PUBLIC = 0x0001;	// class field method
const int ACC_PRIVATE = 0x0002;	//       field method
const int ACC_PROTECTED = 0x0004;	//   field method
const int ACC_STATIC = 0x0008;	//       field method
const int ACC_FINAL = 0x0010;	// class field method
const int ACC_SUPER = 0x0020;	// ����ʹ��invoke_special�ֽ���ָ���������
const int ACC_SYNCHRONIZED = 0x0020;	//     method
const int ACC_VOLATILE = 0x0040;	//   field �ֶ�Ϊvolatile
const int ACC_BRIDGE = 0x0040;	//             method Ϊ�������������Žӷ���
const int ACC_TRANSIENT = 0x0080;	//   field �ֶ�Ϊtransient
const int ACC_VARARGS = 0x0080;	//             method �������ղ�������
const int ACC_NATIVE = 0x0100;	//             method
const int ACC_INTERFACE = 0x0200;	//��ʶһ���ӿ�
const int ACC_ABSTRACT = 0x0400;	// class method
const int ACC_STRICT = 0x0800;	//             method ����Ϊstrictfp
const int ACC_SYNTHETIC = 0x1000;	//�ࡢ�ֶΡ��������ɱ������Զ�������
const int ACC_ANNOTATION = 0x2000;
const int ACC_ENUM = 0x4000;


