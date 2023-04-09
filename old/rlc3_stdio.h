/*
	Name: rlc3_stdio.h
	Copyright: GPL 3.9
	Author: 瞿相荣 
	Date: 26/03/23 21:24
	Description: RLC3标准IO，临时，将会在后面扩展
*/

#ifndef RLC3_STDIO_H
#define RLC3_STDIO_H

#include"io.h"

#include"stdio.h"

/*临时，将会在后面扩展*/

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
