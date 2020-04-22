#include "similarityMatrix.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum)
{
	int* similarityMatix = malloc(sizeof(int) * (seqNum * (seqNum - 1) / 2));
	
	for (int i = 0; i < seqNum; i++)
	{
		for (int j = i + 1; j < seqNum; j++)
		{
			char* seq1 = (char*)malloc((seqArray[i]->len_str + 1) * sizeof(char));
			char* seq2 = (char*)malloc((seqArray[j]->len_str + 1) * sizeof(char));

			strcpy(seq1, seqArray[i]->str);
			strcpy(seq2, seqArray[j]->str);

			seq1[seqArray[i]->len_str] = '$';
			seq1[seqArray[i]->len_str+1] = '\0';
			seq2[seqArray[j]->len_str] = '$';
			seq2[seqArray[j]->len_str+1] = '\0';

			char* l_seq = (char*)malloc((strlen(seq1) + strlen(seq1)) * sizeof(char));
			strcpy(l_seq, seq1);
			strcat(l_seq, seq2);

			Node* gstHead = Build_GSTree(l_seq, seq1, seq2);

			LcsCoordinate* lcs = Get_LCS(gstHead);

			//your stuff here
			int A = GetAlignmentValue("ACATGC", 6, "ACACT", 5, -5, -2, 1, -2);
			int B = lcs->x2-lcs->x1;
			int C = GetAlignmentValue("ACATGC", 6, "ACACT", 5, -5, -2, 1, -2);;

			//insert a value into matrix
			similarityMatix[(j*(j - 1) / 2) + i] = A+B+C;
		}
	}

	return similarityMatix;
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