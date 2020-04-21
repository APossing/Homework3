#include "similarityMatrix.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum)
{
	//Create matrix, think you should do it, not reall sure what and how

	for (int i = 0; i < seqNum; i++)
	{
		for (int j = i + 1; j < seqNum; j++)
		{
			char* seq1 = (char*)malloc((seqArray[i]->len_str + 1) * sizeof(char));
			char* seq2 = (char*)malloc((seqArray[j]->len_str + 1) * sizeof(char));

			strcpy(seq1, seqArray[i]->str);
			strcpy(seq2, seqArray[j]->str);

			seq1[seqArray[i]->len_str] = '$';
			seq2[seqArray[j]->len_str] = '$';

			Node* gstHead = Build_GSTree(seq1, seq2);

			LcsCoordinate* lcs = Get_LCS(gstHead);

			//your stuff here


			//insert a value into matrix
		}
	}

	//should return a matrix or should ouput it, or what ever XD
}