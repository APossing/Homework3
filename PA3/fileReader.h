#ifndef FILEREADER_H
#define FILEREADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define TRUE 1
#define FALSE 0

typedef struct sequence
{
	int str_name_len;
	int len_str;

	char* str_name;
	char* str;

	struct sequence* pNext;
	struct sequence* pPrev;
} Sequence;

typedef struct seq_list
{
	struct sequence* pHead;
	struct sequence* pTail;
}Seq_List;

Sequence* get_sequence(char* file_name);

Sequence* init_sequence(void);

Seq_List* init_list(void);

bool insert_seq(Seq_List* list, Sequence* seq_node);

char* get_alphabet(char* file_name);



#endif