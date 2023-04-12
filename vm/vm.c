/*
	Name: vm.c
	Copyright: GPL 3.9
	Author: ������
	Date: 26/03/23 21:24
	Description: �����Դ�ļ�
*/

#ifndef RLC3_VM_C
#define RLC3_VM_C

#include"stdio.h"
#include"stdlib.h"

#include"exception.h"
#include"bcrunner.h"
#include"meminit.h"

#define BEF "BAD EXECUTABEL FILE"
#define CHECK_EXE_END \
	if(ftell(fp)==fsize) {\
		THROW(BEF)\
	}
//��Լ���������ڼ���ִ���ļ���ʽ
#define CATCH_RETURN(RetVal) \
	CATCH {\
		return RetVal;\
	}
//��Լ�����������ж��Ƿ񱨴�
#define CATCH_EXE_END \
	CHECK_EXE_END\
	CATCH_RETURN(-1)
//��Լ��������CHECK_EXE_END��CATCH_EXE_END�Ľ����
char* cmd_code;

int getFileSize(FILE* fp) {
	//���fpָ���ļ��Ĵ�С������fp�ûؿ�ͷ
	fseek(fp, 0, SEEK_END);
	return ftell(fp);
	fseek(fp, 0, SEEK_SET);
}

uint16 RLC3_Interpret(FILE* fp) {
	//������ִ���ļ���������������У������ֽ���ִ�к�ķ���ֵ
	int fsize = getFileSize(fp);
	char meminit_mode;				//�ڴ��ʼ��ģʽ
	uint32 main_addr;			//����ʼִ�еĵ�ַ

	fseek(fp, 0, SEEK_SET);

	//�ȳ�ʼ���ڴ�
	fread(&meminit_mode, 1, 1, fp);

	if(meminit_mode == MemImageType) {
		//�ڴ澵��
		if(GetMemImage(fp, mem)!=MEM_MAX) {
			THROW(BEF)
			return -1;
		}
	}

	if(meminit_mode == MemTokenType) {
		//�ڴ�����
		GetMemToken(fp, mem);
	}
	CATCH_EXE_END

	//���ų�ʼ���Ĵ���
	fread(&reg, R_COUNT, sizeof(uint16), fp);
	CATCH_EXE_END

	//Ȼ���ȡ��ʼִ�еĵ�ַ
	fread(&main_addr, 1, sizeof(uint32), fp);
	CATCH_EXE_END
	
	int program_size = fsize - ftell(fp);
	char* byte_code = (char*)calloc(program_size, sizeof(char));
	fread(byte_code, program_size, sizeof(char), fp);
	
	//����β��������ִ�г��� 
	fclose(fp);
	BCODE_INIT(byte_code)
	uint16 ret_val = bc_execute(main_addr);
	
	CATCH_RETURN(-1)
	
	return ret_val;
}

int main(int argc, char* argv[]) {
	if(argc!=2) {
		printf("RLC3: CommandError: bad arguments\n");
		return -1;
	}
	
	IO_INIT(argc, argv)
	IO_BIND();
	
	FILE* fp = fopen(argv[1], "r");
	uint16 ret_val = RLC3_Interpret(fp);
	
	CATCH {
		printf("RLC3: RuntimeError: %s\n", ERROR);
		return -1;
	}
	
	return ret_val;
}

#endif
