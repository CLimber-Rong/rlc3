/*
	Name: io.h
	Copyright: GPL 3.0
	Author: ������ 
	Date: 26/03/23 21:26
	Description: IOʵ�� 
*/

#ifndef RLC3_IO_H
#define RLC3_IO_H

#include"exception.h"
#include"mem.h"
#include"cpu.h"

/*�ڴ˴�����IO�˿��������65536��*/
#define IN_PORT_MAX 65536		//Ĭ��65536 
#define OUT_PORT_MAX 65536		//Ĭ��65536
/*----------*/

int vm_argc; 				//�����в������� 
char** vm_argv;			//�����в��� 

#define IO_INIT(argc, argv) vm_argc = argc; vm_argv = argv;			//�������в�����ʼ�� 
#define IN_BIND(port, function) in_function[port] = function;		//in�� 
#define OUT_BIND(port, function) out_function[port] = function;		//out��
/*
 * ��Ҫ��һ��IO��ֻ��Ҫ��������꼴�ɣ���Ҫ��out_1234�����󶨵�1234����˿ڣ�ֻ��Ҫ��
 * OUT_BIND(1234, out_1234)		//����Ҫ��ĩβ���Ϸֺ�
 * �����Դ����� 
 */ 

typedef void(*IO_FUNCTION_POINT)(uint16 arg);

IO_FUNCTION_POINT in_function[IN_PORT_MAX];
IO_FUNCTION_POINT out_function[OUT_PORT_MAX];

#include"rlc3_stdio.h"			//rlc3�ṩ��һЩ������io���û����Լ������ 

void IO_BIND() {
	/*��������Ӱ�*/
	OUT_BIND(0, out_putchar)
	OUT_BIND(1, out_putint)
	IN_BIND(0, in_inputInt)
	/*----------*/
}

#endif 
