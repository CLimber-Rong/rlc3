/*
	Name: memory.h
	Copyright: GPL 3.0
	Author: ������ 
	Date: 26/03/23 21:25
	Description: �洢�� 
*/

#ifndef RLC3_memory_H
#define RLC3_memory_H


//ģ��洢��

typedef unsigned short uint16;
#define UINT16_MAX 65536

/*�������Ҫ�����ڴ桢ջ���������ã����������*/
#define mem_MAX UINT16_MAX			//Ĭ��128Kb
#define STACK_MAX UINT16_MAX 		//Ĭ��128Kb 
#define PC_STACK_MAX 1024*1024/4	//Ĭ��1Mb 
/*----------*/

enum {
    mem_type = 0, reg_type, num_type			//mem_type�ƺ�û�ã��ȸ��ã�������û�ú��ھ�ɾ�� 
} memory_Type;

enum {
    //�˸�ͨ�üĴ�����r0~r7��
    R_R0 = 0, R_R1, R_R2, R_R3,
    R_R4, R_R5, R_R6, R_R7,
    R_COND, R_COUNT 			//������־λ���Ĵ�������
} Register_ID;

#define REG(register_id) reg_type, R_R##register_id
#define NUM(number) num_type, number

enum {
    COND_GREATER = 1<<0, COND_EQUAL=1<<1, COND_LESS=1<<2
} COND_ID;

enum {
    OP_ADD = 0, OP_SUB, OP_MUL, OP_DIV, OP_AND, OP_OR, OP_NOT, OP_SHL, OP_SHR, OP_MOV,
    OP_LD, OP_LDI, OP_ST, OP_STI, OP_PUSH, OP_POP,
    OP_CMP, OP_BR, OP_JMP, OP_CALL, OP_RET, OP_IN, OP_OUT, OP_COUNT
} Code_ID;

uint16 reg[R_COUNT] = {0};						//�Ĵ���
uint16 stack[STACK_MAX] = {0};					//�ڴ�ջ
uint16 mem[mem_MAX] = {0};						//�ڴ�
unsigned int pc_stack[PC_STACK_MAX] = {0};		//����ջ
unsigned int stack_len = 0;			//ջ����
unsigned int pc_stack_len = 0;		//����ջ����
unsigned int pc;	//���������

#endif
