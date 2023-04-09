/*
	Name: vm.c
	Copyright: GPL 3.9
	Author: 瞿相荣 
	Date: 26/03/23 21:24
	Description: 这是一个示例程序，这个程序的作用是输入一个ASCII码并输出对应字符
*/

#include"stdio.h"
#include"cpu.h"

int main(int argc, char* argv[]) {
	IO_INIT(argc, argv);
	IO_BIND();
	
	op_mov(R_R0, NUM(514));
	op_cmp(REG(0), NUM(514));
	op_br(COND_GREATER|COND_LESS, 1145);
	printf("%d", pc);
	
	return 0;
}
