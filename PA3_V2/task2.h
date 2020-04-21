#ifndef TASK2_H
#define TASK2_H
#include <limits.h>
#include <stdlib.h>

typedef struct dP_cell {
	int substitutionScore;
	int deletionScore;
	int insertionScore;
} DP_cell;
DP_cell* FillInCell(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
DP_cell* CalculateCell(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
DP_cell* GetCalculatedCell(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
int GetMaxSubScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
int GetMaxDeletionScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
int GetMaxInsertionScore(int row, int col, int h, int g, int match, int mismatch, DP_cell** table, char* s1, char* s2);
int GetAlignmentValue(char* s1, int s1Length, char* s2, int s2Length, int h, int g, int match, int mismatch);
int GetCellMax(DP_cell* cell);
void PrintTable(DP_cell** table, int rows, int cols);
#endif

