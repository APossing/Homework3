#include "similarityMatrix.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum)
{
	//Create matrix, think you should do it, not reall sure what and how

	for (int i = 0; i < seqNum; i++)
	{
		for (int j = i + 1; j < seqNum; j++)
		{
			char* seq1 = seqArray[i]->str;
			char* seq2 = seqArray[j]->str;
			Node* gstHead = Build_GSTree(seq1, seq2);

			LcsCoordinate* lcs = Get_LCS(gstHead);

			//your stuff here


			//insert a value into matrix
		}
	}

	//should return a matrix or should ouput it, or what ever XD
}