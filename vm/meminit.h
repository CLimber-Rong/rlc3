#ifndef RLC3_memoryINIT_H
#define RLC3_memoryINT_H

#include"stdio.h"
#include"bcrunner.h"

/*
 * 有些时候，用户希望虚拟机在开启的时候能够初始化自己指定的内存
 * 于是，我们规定了内存初始文件这个概念，虚拟机可以通过内存初始文件初始化内存
 * 内存初始文件有两种存储格式：内存镜像和内存描述文件
 * 其中内存镜像初始化速度快，但是占用空间大：无论内容如何，永远占1sizeof(uint16)8kb
 * 其中的内存描述文件初始化速度相对不算快（其格式的本质是词法分析），但是会尽可能的消除冗余（无论内存碎片大小，都只用四个字节表示）
	 * 需要注意的是：内存描述文件的大小是不定的，其大小取决于内存碎片的数量和大小
	 * 这也就意味着，有些情况下，内存描述文件容量是大于1sizeof(uint16)8kb的，此时内存镜像才是明智的选择
 * 为此，我将提供内存描述文件、内存镜像的存储功能，并提供比较两者大小的函数
 */

//这段代码不知道有没有用，没有就删掉
//enum {
//    token_number = 0, token_zero
//} token_type;
//
//typedef struct {
//	token_type;
//	int info;			//如果是内存碎片token，则info用来储存内存碎片大小
//} memoryToken;

//typedef struct memoryTokenListStruct {
//	//因为内存描述文件是一串一旦确定就不会更改的不定长列表，所以用链表最为合适了
//	MemToken token;
//	struct memoryTokenListStruct* next;
//} memoryTokenList;

int GetMemImage(FILE* fp, uint16* memory) {
	return fread(memory, sizeof(uint16), 64*1024, fp);
}

int WriteMemImage(FILE* fp, uint16* memory) {
	return fwrite(memory, sizeof(uint16), 64*1024, fp);
}

void GetMemToken(FILE* fp, uint16* memory) {
	//将fp的内存描述写入memory
	int i = 0;
	while(i<64*1024) {
		uint16 token_head;
		fread(&token_head, sizeof(uint16), 1, fp);
		if(token_head!=0) {
			memory[i] = token_head;
		} else {
			uint16 zero_size;		//内存碎片大小
			fread(&zero_size, sizeof(uint16), 1, fp);
			while(zero_size!=0) {		//将memory[i..i+zero_size]全部置零，并让i+=zero_size
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
	while(i<64*1024) {
		if(memory[i]!=0) {
			fwrite(&memory[i], sizeof(uint16), 1, fp);
		} else {
			uint16 zero_size = 1;
			while(memory[i+zero_size]==0&&i+zero_size<64*1024) {
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
	//返回1则代表内存镜像容量最优，返回0则代表内存描述最优
	int i = 0;
	int token_size = 0;		//内存描述所需要的容量，如果他大于128kb，则内存镜像最优
	while(i<64*1024) {
		if(token_size >= 64*1024) {
			return 1;
		}

		if(memory[i]!=0) {
			token_size++;
			i++;
		} else {
			token_size += 2;		//需要两个uint16
			while(memory[i]==0) {
				i++;
			}
		}
	}

	return 0;
}

#endif
