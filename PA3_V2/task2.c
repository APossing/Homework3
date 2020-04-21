#include "task2.h"
#include <stdio.h>

int GetCellMax(DP_cell* cell)
{
	int max = cell->substitutionScore;
	if (cell->deletionScore > max)
		max = cell->deletionScore;
	if (cell->insertionScore > max)
		max = cell->insertionScore;
	return max;
}


DP_cell* FillInCell(int row, int col, int subScore, int delScore, int insScore, DP_cell* table[])
{
	//if (!IsValidCell(row, col))
	//	return nullptr;
	table[row][col].substitutionScore = subScore;
	table[row][col].deletionScore = delScore;
	table[row][col].insertionScore = insScore;
	return &table[row][col];
}

DP_cell* CalculateCell(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2)
{
	int minValue = INT_MIN - h - g + 1;
	if (row == 0 && col == 0)
		return FillInCell(row, col, 0, minValue, minValue, table);
	if (row == 0)
		return FillInCell(row, col, minValue, h + col * g, minValue, table);
	if (col == 0)
		return FillInCell(row, col, minValue, minValue, h + row * g, table);

	int subScore = GetMaxSubScore(row, col, h, g, match, mismatch, table, s1, s2);
	int delScore = GetMaxDeletionScore(row, col, h, g, match, mismatch, table, s1, s2);
	int insScore = GetMaxInsertionScore(row, col, h, g, match, mismatch, table, s1, s2);

	return FillInCell(row, col, subScore, delScore, insScore, table);
}

DP_cell* GetCalculatedCell(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2)
{
	//if (table->IsValidCell(row, col))
	//{
	DP_cell* cell = &table[row][col];
	if (cell == NULL)
		cell = CalculateCell(row, col, h, g, match, mismatch, table, s1, s2);
	return cell;
	//}
	//return nullptr;
}

int GetMaxSubScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2)
{
	int matchScore = mismatch;
	if (s1[row - 1] == s2[col - 1])
		matchScore = match;

	DP_cell* diagCell = GetCalculatedCell(row - 1, col - 1, h, g, match, mismatch, table, s1, s2);

	return GetCellMax(diagCell) + matchScore;
}
int GetMaxDeletionScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2)
{
	DP_cell* upCell = GetCalculatedCell(row - 1, col, h, g, match, mismatch, table, s1, s2);
	int max = upCell->deletionScore + g;

	if (upCell->insertionScore + h + g > max)
		max = upCell->insertionScore + h + g;
	if (upCell->substitutionScore + h + g > max)
		max = upCell->substitutionScore + h + g;

	return max;
}

int GetMaxInsertionScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2)
{
	DP_cell* leftCell = GetCalculatedCell(row, col - 1, h, g, match, mismatch, table, s1, s2);
	int max = leftCell->deletionScore + h + g;

	if (leftCell->insertionScore + g > max)
		max = leftCell->insertionScore + g;
	if (leftCell->substitutionScore + h + g > max)
		max = leftCell->substitutionScore + h + g;

	return max;
}

int GetAlignmentValue(char* s1, int s1Length, char* s2, int s2Length, int h, int g, int match, int mismatch)
{
	DP_cell** table = malloc(sizeof(DP_cell*) * s1Length+1);
	for (int i = 0; i < s1Length+1; i++)
		table[i] = malloc(sizeof(DP_cell) * s2Length+1);


	for (int row = 0; row <= s1Length; row++)
		for (int col = 0; col <= s2Length; col++)
			CalculateCell(row, col, h, g, match, mismatch, table, s1, s2);

	PrintTable(table, s1Length + 1, s2Length + 1);
	int b = 5;
}

void PrintTable(DP_cell** table, int rows, int cols)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			DP_cell cell = table[i][j];
			printf("(%d)-(%d)-(%d)\t",cell.insertionScore, cell.substitutionScore, cell.deletionScore);
		}
		printf("\n");
	}

}