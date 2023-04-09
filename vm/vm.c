/*
	Name: vm.c
	Copyright: GPL 3.9
	Author: 瞿相荣
	Date: 26/03/23 21:24
	Description: 这是一个示例程序，这个程序的作用是输入一个ASCII码并输出对应字符
*/

#include"stdio.h"
#include"stdlib.h"
#include"meminit.h"
//9 0 0 2 0 0 9 0 1 2 0 72 22 0 0 0 1
//9 0 0 2 0 0 9 0 1 2 0 101 22 0 0 0 1
//9 0 0 2 0 0 9 0 1 2 0 108 22 0 0 0 1
//9 0 0 2 0 0 9 0 1 2 0 108 22 0 0 0 1
//9 0 0 2 0 0 9 0 1 2 0 111 22 0 0 0 1 20

//char cmd_code[] = {
//	OP_MOV, 0, R_R0, num_type, 0, 0,
//	OP_MOV, 0, R_R1, num_type, 0, 72,
//	OP_OUT, 0, R_R0, 0, R_R1,
//	OP_RET
//};

char* cmd_code;

int getFileSize(FILE* fp) {
	//获得fp指定文件的大小，并将fp置回开头
	fseek(fp, 0, SEEK_END);
	return ftell(fp);
}

int main(int argc, char* argv[]) {

//	if(argc!=2) {
//		printf("Error: bad arguments");
//		return 0;
//	}
//
//	IO_INIT(argc, argv);
//	IO_BIND();
//
//	FILE* fp = fopen(argv[1], "r");
//	int fsize = getFileSize(fp);
//	cmd_code = (char*)calloc(sizeof(char), fsize);
//	fread(cmd_code, sizeof(char), fsize, fp);
//
//	BCODE_INIT(cmd_code);
//
//	bc_execute(0);
//
//	return 0;
	mem[0] = 1145;
	mem[43] = 14;
	mem[1919] = 1919;
	mem[810] = 810;
	printf("%d\n", CompareMemFormat(mem));
	FILE* fp;
	
	fp = fopen("mem.img", "w");
	WriteMemToken(fp, mem);
	fclose(fp);
	
	fp = fopen("mem.img", "r");
	GetMemToken(fp, mem);
	printf("%d\n", mem[43]);
	fclose(fp);
}
