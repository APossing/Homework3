#include "similarityMatrix.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum)
{
	int* similarityMatix = malloc(sizeof(int) * (seqNum * (seqNum - 1) / 2));
	
	for (int i = 0; i < seqNum; i++)
	{
		for (int j = i + 1; j < seqNum; j++)
		{
			char* seq1 = seqArray[i]->str;
			char* seq2 = seqArray[j]->str;
			Node* gstHead = Build_GSTree(seq1, seq2);

			LcsCoordinate* lcs = Get_LCS(gstHead);

			//your stuff here
			int A = 1;
			int B = 2;
			int C = 4;

			//insert a value into matrix
			similarityMatix[(j*(j - 1) / 2) + i] = A+B+C;
		}
	}

	//should return a matrix or should output it, or what ever XD
}


void Print_Simularity_Matrix(int* matrix, int seqNum)
{
	printf("\n");
	printf("\n");
	for (int i = 0; i < seqNum; i++)
	{
		printf("S%d\t", i);
	}
	printf("\n");
	for (int i = 1; i < seqNum; i++)
	{
		printf("S%d", i);
		for (int j = 0; j < i; j++)
		{
			printf("%d\t", matrix[(i * (i - 1) / 2) + j]);
		}
		printf("\n");
	}
}