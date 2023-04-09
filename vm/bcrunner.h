/*
	Name: bcrunner.h
	Copyright: GPL3.0
	Author: 瞿相荣 
	Date: 05/04/23 15:42
	Description: 字节码运行文件 
*/


#ifndef RLC3_BCRUNNER_H
#define RLC3_BCRUNNER_H

#include"cpu.h"
#define PC pc_stack[pc_stack_len]
#define BCODE(offset) bcode[PC+offset]

#define u16(high, low) ((uint16) high<<8 | low)
#define u32(h1, h2, l1, l2) ((uint32) h1<<24 | h2<<16 | l1<<8 | l2)

typedef unsigned int uint32;

char* bcode;				//字节码
void* op_func_arr[OP_COUNT];

#define BCODE_INIT(bc) bcode = bc;

//为了节约函数，接下来也会像cpu.h一样定义宏来减少冗余
#define CASE_MATH_FUNCTION(OP_CODE, FunctionName) \
	case OP_CODE: {\
		FunctionName(u16(BCODE(1), BCODE(2)), BCODE(3), u16(BCODE(4), BCODE(5)), BCODE(6), u16(BCODE(7), BCODE(8)));\
		PC += 8+1;\
		break;\
	}

#define CASE_MOV_FUNCTION(OP_CODE, FunctionName) \
	case OP_CODE: {\
		FunctionName(u16(BCODE(1), BCODE(2)), BCODE(3), u16(BCODE(4), BCODE(5)));\
		PC += 5+1;\
		break;\
	}


#define CASE_IO_FUNCTION(OP_CODE, FunctionName) \
	case OP_CODE: {\
		FunctionName(u16(BCODE(1), BCODE(2)), u16(BCODE(3), BCODE(4)));\
		CATCH {\
			return -1;\
		}\
		PC += 5;\
		break;\
	}


uint16 bc_execute(uint32 origin) {
	pc = origin;
	op_call(origin);
	while(pc_stack_len!=0) {
		//执行一条指令
		char cmd = bcode[PC];
		switch(cmd) {
				CASE_MATH_FUNCTION(OP_ADD, op_add)
				CASE_MATH_FUNCTION(OP_SUB, op_sub)
				CASE_MATH_FUNCTION(OP_MUL, op_mul)
				CASE_MATH_FUNCTION(OP_DIV, op_div)
				CASE_MATH_FUNCTION(OP_AND, op_and)
				CASE_MATH_FUNCTION(OP_OR, op_or)
				CASE_MATH_FUNCTION(OP_SHL, op_shl)
				CASE_MATH_FUNCTION(OP_SHR, op_shr)

			case OP_NOT: {
				op_not(u16(BCODE(1), BCODE(2)));
				PC += 2+1;
				break;
			}

			CASE_MOV_FUNCTION(OP_MOV, op_mov)
			CASE_MOV_FUNCTION(OP_LD, op_ld)
			CASE_MOV_FUNCTION(OP_LDI, op_ldi)
			CASE_MOV_FUNCTION(OP_ST, op_st)
			CASE_MOV_FUNCTION(OP_STI, op_sti)

			case OP_PUSH: {
				op_push(u16(BCODE(1), BCODE(2)));
				PC += 2+1;
				break;
			}

			case OP_POP: {
				op_pop(BCODE(1), u16(BCODE(2), BCODE(3)));
				PC += 3+1;
				break;
			}

			case OP_CMP: {
				op_pop(BCODE(1), u16(BCODE(2), BCODE(3)));
				PC += 3+1;
				break;
			}

			case OP_BR: {
				op_pop(u16(BCODE(1), BCODE(2)), u32(BCODE(3), BCODE(4), BCODE(5), BCODE(6)));
				PC += 6+1;
				break;
			}

			case OP_JMP: {
				op_jmp(u32(BCODE(1), BCODE(2), BCODE(3), BCODE(4)));
				PC += 6+1;
				break;
			}

			case OP_CALL: {
				uint32 call_addr = u32(BCODE(1), BCODE(2), BCODE(3), BCODE(4));
				PC += 4+1;
				op_call(call_addr);
				break;
			}

			case OP_RET: {
				op_ret();
				PC += 1;
				break;
			}

			CASE_IO_FUNCTION(OP_IN, op_in)
			CASE_IO_FUNCTION(OP_OUT, op_out)

			default: {
				THROW("UKNOWN CMD")
				return -1;
			}
		}
	}

	return reg[R_R0];
}

#endif
