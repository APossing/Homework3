#ifndef SIMILARITYMATRIX_H
#define SIMILARITYMATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "st.h"
#include "fileReader.h"
#include "task2.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum);
void Print_Simularity_Matrix(int* matrix, int seqNum);
char* Get_String_Reverse(char* str, int length);
#endif