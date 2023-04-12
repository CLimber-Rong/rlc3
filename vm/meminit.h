/*
	Name: meminit.h
	Copyright: GPL3.0
	Author: ������
	Date: 09/04/23 14:14
	Description: �ڴ��ʼ��
*/


#ifndef RLC3_MEMINIT_H
#define RLC3_MEMINIT_H

#include"stdio.h"
#include"bcrunner.h"

/*
 * ��Щʱ���û�ϣ��������ڿ�����ʱ���ܹ���ʼ���Լ�ָ�����ڴ�
 * ���ǣ����ǹ涨���ڴ��ʼ�ļ����������������ͨ���ڴ��ʼ�ļ���ʼ���ڴ�
 * �ڴ��ʼ�ļ������ִ洢��ʽ���ڴ澵����ڴ������ļ�
 * �����ڴ澵���ʼ���ٶȿ죬����ռ�ÿռ������������Σ���Զռ1sizeof(uint16)8kb
 * ���е��ڴ������ļ���ʼ���ٶ���Բ���죨���ʽ�ı����Ǵʷ������������ǻᾡ���ܵ��������ࣨ�����ڴ���Ƭ��С����ֻ���ĸ��ֽڱ�ʾ��
	 * ��Ҫע����ǣ��ڴ������ļ��Ĵ�С�ǲ����ģ����Сȡ�����ڴ���Ƭ�������ʹ�С
	 * ��Ҳ����ζ�ţ���Щ����£��ڴ������ļ������Ǵ���1sizeof(uint16)8kb�ģ���ʱ�ڴ澵��������ǵ�ѡ��
 * Ϊ�ˣ��ҽ��ṩ�ڴ������ļ����ڴ澵��Ĵ洢���ܣ����ṩ�Ƚ����ߴ�С�ĺ���
 */

enum {
    MemImageType = 0, MemTokenType
} MemInitType;

int GetMemImage(FILE* fp, uint16* memory) {
	return fread(memory, sizeof(uint16), MEM_MAX, fp);
}

int WriteMemImage(FILE* fp, uint16* memory) {
	return fwrite(memory, sizeof(uint16), MEM_MAX, fp);
}

void GetMemToken(FILE* fp, uint16* memory) {
	//��fp���ڴ�����д��memory
	int i = 0;
	while(i<MEM_MAX) {
		uint16 token_head;
		fread(&token_head, sizeof(uint16), 1, fp);
		if(token_head!=0) {
			memory[i] = token_head;
		} else {
			uint16 zero_size;		//�ڴ���Ƭ��С
			fread(&zero_size, sizeof(uint16), 1, fp);
			while(zero_size!=0) {		//��memory[i..i+zero_size]ȫ�����㣬����i+=zero_size
				memory[i] = 0;
				i++;
				zero_size--;
			}
		}
		i++;
	}
}

void WriteMemToken(FILE* fp, uint16* memory) {
	const uint16 zero = 0;
	int i=0;
	while(i<MEM_MAX) {
		if(memory[i]!=0) {
			fwrite(&memory[i], sizeof(uint16), 1, fp);
		} else {
			uint16 zero_size = 1;
			while(memory[i+zero_size]==0&&i+zero_size<MEM_MAX) {
				zero_size++;
			}
			fwrite(&zero, sizeof(uint16), 1, fp);
			fwrite(&zero_size, sizeof(uint16), 1, fp);
			i += zero_size;
		}
		i++;
	}
}

int CompareMemFormat(uint16* memory) {
	//����1������ڴ澵���������ţ�����0������ڴ���������
	int i = 0;
	int token_size = 0;		//�ڴ���������Ҫ�����������������2*MEM_MAX kb�����ڴ澵������
	while(i<MEM_MAX) {
		if(token_size >= MEM_MAX) {
			return 1;
		}

		if(memory[i]!=0) {
			token_size++;
			i++;
		} else {
			token_size += 2;		//��Ҫ����uint16
			while(memory[i]==0) {
				i++;
			}
		}
	}

	return 0;
}

#endif
