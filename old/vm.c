/*
	Name: vm.c
	Copyright: GPL 3.9
	Author: ������ 
	Date: 26/03/23 21:24
	Description: ����һ��ʾ������������������������һ��ASCII�벢�����Ӧ�ַ�
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
