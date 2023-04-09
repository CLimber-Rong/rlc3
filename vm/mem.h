/*
	Name: memory.h
	Copyright: GPL 3.0
	Author: 瞿相荣 
	Date: 26/03/23 21:25
	Description: 存储器 
*/

#ifndef RLC3_memory_H
#define RLC3_memory_H


//模拟存储器

typedef unsigned short uint16;
#define UINT16_MAX 65536

/*如果你想要更改内存、栈的容量配置，请更改这里*/
#define mem_MAX UINT16_MAX			//默认128Kb
#define STACK_MAX UINT16_MAX 		//默认128Kb 
#define PC_STACK_MAX 1024*1024/4	//默认1Mb 
/*----------*/

enum {
    mem_type = 0, reg_type, num_type			//mem_type似乎没用，先搁置，如果真的没用后期就删掉 
} memory_Type;

enum {
    //八个通用寄存器（r0~r7）
    R_R0 = 0, R_R1, R_R2, R_R3,
    R_R4, R_R5, R_R6, R_R7,
    R_COND, R_COUNT 			//条件标志位，寄存器个数
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

uint16 reg[R_COUNT] = {0};						//寄存器
uint16 stack[STACK_MAX] = {0};					//内存栈
uint16 mem[mem_MAX] = {0};						//内存
unsigned int pc_stack[PC_STACK_MAX] = {0};		//函数栈
unsigned int stack_len = 0;			//栈长度
unsigned int pc_stack_len = 0;		//函数栈长度
unsigned int pc;	//程序计数器

#endif
