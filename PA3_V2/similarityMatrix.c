#include "similarityMatrix.h"

int* Compute_Similarity_Matrix(Sequence** seqArray, int seqNum)
{
	ConcatSequence* c = BuildConcatSequence(seqArray, seqNum);
	
	int* similarityMatix = malloc(sizeof(int) * (seqNum * (seqNum - 1) / 2));
	
	Node* root = Build_GSTree(c->str, c->starIndexes, c->starIndexCount);

	AdamFingerprint* fingerPrints = malloc(sizeof(AdamFingerprint) * seqNum);
	for (int i = 0; i < seqNum; i++)
		fingerPrints[i].count = 0;
	
	GetFingerPrints(root, fingerPrints, mix_colour);

	for (int i = 0; i < seqNum; i++)
		fingerPrints[i].count++;
	
	for (int i = 0; i < seqNum; i++)
	{
		for (int j = i + 1; j < seqNum; j++)
		{
			char* seq1 = (char*)malloc((seqArray[i]->len_str + 1) * sizeof(char));
			char* seq2 = (char*)malloc((seqArray[j]->len_str + 1) * sizeof(char));

			strcpy(seq1, seqArray[i]->str);
			strcpy(seq2, seqArray[j]->str);

			seq1[seqArray[i]->len_str] = '$';
			seq1[seqArray[i]->len_str + 1] = '\0';
			seq2[seqArray[j]->len_str] = '$';
			seq2[seqArray[j]->len_str + 1] = '\0';

			char* l_seq = (char*)malloc((strlen(seq1) + strlen(seq1)) * sizeof(char));
			strcpy(l_seq, seq1);
			strcat(l_seq, seq2);

			int temp_seq[2] = {0, seqArray[i]->len_str+1};

			Node* gstHead = Build_GSTree(l_seq, temp_seq, 2);

			
			LcsCoordinate* lcs = Get_LCS(gstHead);

			//your stuff here
			char* s1StartReversed = Get_String_Reverse(seq1, lcs->x1);
			char* s2StartReversed = Get_String_Reverse(seq2, lcs->y1);
			int A = GetAlignmentValue(s1StartReversed, lcs->x1, s2StartReversed, lcs->y1, -5, -2, 1, -2);
			
			int B = lcs->x2-lcs->x1+1;
			
			char* s1EndStart = seq1 + lcs->x2 + 1;
			int s1EndStartLength = seqArray[i]->len_str - lcs->x2-1;
			char* s2EndStart = seq2 + lcs->y2 + 1;
			int s2EndStartLength = seqArray[j]->len_str - lcs->y2-1;
			
			int C = GetAlignmentValue(s1EndStart,s1EndStartLength ,s2EndStart ,s2EndStartLength, -5, -2, 1, -2);;

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

char* Get_String_Reverse(char* str, int length)
{
	char* returnStr = malloc(sizeof(char) * length);
	for(int i = length-1; i >= 0; i--)
	{
		returnStr[length - 1 - i] = str[i];
	}
	return returnStr;
}

ConcatSequence* BuildConcatSequence(Sequence** seqArray, int seqNum)
{
	ConcatSequence* concat = malloc(sizeof(ConcatSequence));
	concat->starIndexCount = seqNum;
	concat->starIndexes = malloc(sizeof(int) * seqNum);
	
	int length = 0;
	for (int i = 0; i < seqNum; i++)
	{
		length += seqArray[i]->len_str + 1;
	}
	concat->str = malloc(sizeof(char) * length+1);
	concat->strLength = length;
	int curLocation = 0;
	for (int i = 0; i < seqNum; i++)
	{
		concat->starIndexes[i] = curLocation;
		strcpy(concat->str + curLocation, seqArray[i]->str);
		curLocation += seqArray[i]->len_str;
		concat->str[curLocation++] = '$';
		concat->str[curLocation] = '\0';
	}
	return concat;
}