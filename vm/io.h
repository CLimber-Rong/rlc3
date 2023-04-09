/*
	Name: io.h
	Copyright: GPL 3.0
	Author: 瞿相荣 
	Date: 26/03/23 21:26
	Description: IO实现 
*/

#ifndef RLC3_IO_H
#define RLC3_IO_H

#include"exception.h"
#include"mem.h"
#include"cpu.h"

/*在此处定义IO端口数，最多65536个*/
#define IN_PORT_MAX 65536		//默认65536 
#define OUT_PORT_MAX 65536		//默认65536
/*----------*/

int vm_argc; 				//命令行参数个数 
char** vm_argv;			//命令行参数 

#define IO_INIT(argc, argv) vm_argc = argc; vm_argv = argv;			//将命令行参数初始化 
#define IN_BIND(port, function) in_function[port] = function;		//in绑定 
#define OUT_BIND(port, function) out_function[port] = function;		//out绑定
/*
 * 想要绑定一个IO，只需要在下面填宏即可，如要将out_1234函数绑定到1234输出端口，只需要：
 * OUT_BIND(1234, out_1234)		//不需要在末尾加上分号
 * 其余以此类推 
 */ 

typedef void(*IO_FUNCTION_POINT)(uint16 arg);

IO_FUNCTION_POINT in_function[IN_PORT_MAX];
IO_FUNCTION_POINT out_function[OUT_PORT_MAX];

#include"rlc3_stdio.h"			//rlc3提供了一些基本的io，用户可以继续添加 

void IO_BIND() {
	/*在这里添加绑定*/
	OUT_BIND(0, out_putchar)
	OUT_BIND(1, out_putint)
	IN_BIND(0, in_inputInt)
	/*----------*/
}

#endif 
