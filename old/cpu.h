/*
	Name: cpu.h
	Copyright: GPL 3.0
	Author: 瞿相荣 
	Date: 26/03/23 21:27
	Description: 中央处理器 
*/

#ifndef RLC3_CPU_H
#define RLC3_CPU_H

//模拟cpu

#include"exception.h"
#include"mem.h"
#include"io.h"

/*
 * 下面的宏是用来节约行数的，因为加减乘除等的唯一区别就在于函数名和运算符
 * 所以我定义了DEF_OPERATION_FUNCTION（定义运算函数），，你只需要填写函数名和对应的运算符，即可创建一个运算函数
 */

//CheckError代表判错，如防止除数为零
#define DEF_OPERATION_FUNCTION(FunctionName, Operator, CheckError) \
	void FunctionName(uint16 src, int n1_type, uint16 n1, int n2_type, uint16 n2) {\
		if(n1_type==reg_type) {\
			n1 = reg[n1];\
		}\
		if(n2_type==reg_type) {\
			n2 = reg[n2];\
		}\
		CheckError\
		reg[src] = n1 Operator n2;\
	}

//除法判错
#define DIV_CHECK_ERROR if(n2==0){\
		THROW("The divisor cannot be zero");\
		return;\
	}

DEF_OPERATION_FUNCTION(op_add, +,)
DEF_OPERATION_FUNCTION(op_sub, -,)
DEF_OPERATION_FUNCTION(op_mul, *,)
DEF_OPERATION_FUNCTION(op_div, /, DIV_CHECK_ERROR)
DEF_OPERATION_FUNCTION(op_and, &,)
DEF_OPERATION_FUNCTION(op_or, |,)
DEF_OPERATION_FUNCTION(op_shl, <<,)
DEF_OPERATION_FUNCTION(op_shr, >>,)

void op_not(uint16 dst) {
	reg[dst] = ~reg[dst];
}

/*作用同DEF_OPERATION_FUNCTION，这个宏用来定义内存迁移的函数*/
#define DEF_MOVE_FUNCTION(FunctionName, dstName, NumType_src, RegType_src) \
	void FunctionName(uint16 dst, int src_type, uint16 src) {\
		if(src_type==num_type) {\
			dstName = NumType_src;\
		}\
		if(src_type==reg_type) {\
			dstName = RegType_src;\
		}\
	}

DEF_MOVE_FUNCTION(op_mov, reg[dst], src, reg[src])
DEF_MOVE_FUNCTION(op_ld, reg[dst], mem[src], mem[reg[src]])
DEF_MOVE_FUNCTION(op_ldi, reg[dst], mem[mem[src]], mem[mem[reg[src]]])
DEF_MOVE_FUNCTION(op_st, mem[reg[dst]], src, reg[src])
DEF_MOVE_FUNCTION(op_sti, mem[reg[dst]], mem[src], mem[reg[src]])

void op_push(uint16 src) {
	stack[stack_len] = reg[src];
	stack_len++;
}

void op_pop(int dst_type, uint16 dst) {
	//dst_type==num_type代表不弹出到任何寄存器
	stack_len--;
	if(dst_type==reg_type) {
		reg[dst] = stack[stack_len];
	}
}

void op_cmp(int dst_type, uint16 dst, int src_type, uint16 src) {
	//比较dst和src，并将比较结果存入reg[R_COND]
	if(dst_type==reg_type) {
		dst = reg[dst];
	}
	if(src_type==reg_type) {
		src = reg[src];
	}
	if(dst>src) {
		reg[R_COND] = COND_GREATER;
	}
	if(dst==src) {
		reg[R_COND] = COND_EQUAL;
	}
	if(dst<src) {
		reg[R_COND] = COND_LESS;
	}
}

void op_br(uint16 br_code, unsigned int jmp_addr) {
	/*
	 * 这里可能会有点难懂
	 * 不妨做一个等值演算来理解
	 * 真正易懂的代码应该是这么写的
	 if(br_code&1<<0 && reg[R_COND]&1<<0) {
	 	pc = jmp_addr;
	 }
	 if(br_code&1<<1 && reg[R_COND]&1<<1) {
	 	pc = jmp_addr;
	 }
	 ......
	 * 可以发现，这些判断可以整合成一个判断，即下面的代码
	 * 这样做的意义很简单：节约行数，加快运行速度
	 */
	if(br_code&reg[R_COND]!=0) {
		pc = jmp_addr;
	}
}

void op_jmp(unsigned int jmp_addr) {
	pc = jmp_addr;
}

void op_call(unsigned int call_addr) {
	/*备忘：每次执行命令时，先将程序计数器加一，这样call才不会有bug*/
	pc_stack[pc_stack_len] = pc;
	pc_stack_len++;
	pc = call_addr;
}

void op_ret() {
	pc_stack_len--;
	pc = pc_stack[pc_stack_len];
}

/*作用同上*/
#define DEF_IO_FUNCTION(FunctionName, FunctionArrayName) \
	void FunctionName(uint16 port, uint16 arg) {\
		FunctionArrayName[reg[port]](reg[arg]);\
	}

DEF_IO_FUNCTION(op_in, in_function)
DEF_IO_FUNCTION(op_out, out_function)

#endif
