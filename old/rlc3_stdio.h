/*
	Name: rlc3_stdio.h
	Copyright: GPL 3.9
	Author: ������ 
	Date: 26/03/23 21:24
	Description: RLC3��׼IO����ʱ�������ں�����չ
*/

#ifndef RLC3_STDIO_H
#define RLC3_STDIO_H

#include"io.h"

#include"stdio.h"

/*��ʱ�������ں�����չ*/

void out_putchar(uint16 arg) {
	char c = (char)arg;
	putchar(c);
}

void in_inputInt(uint16 arg) {
	uint16 n;
	scanf("%d", &n);
	mem[arg] = n;
}

#endif
