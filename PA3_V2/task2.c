#include "task2.h"
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
	DP_cell** table = malloc(sizeof(DP_cell*) * s1Length + 1);
	for (int i = 0; i < s1Length + 1; i++)
		table[i] = malloc(sizeof(DP_cell) * s2Length + 1);


	for (int row = 0; row <= s1Length; row++)
		for (int col = 0; col <= s2Length; col++)
			CalculateCell(row, col, h, g, match, mismatch, table, s1, s2);

	return TraceBackGlobal(s1Length, s2Length,s1, s2, table, h);
	
	PrintTable(table, s1Length + 1, s2Length + 1);
}

void PrintTable(DP_cell** table, int rows, int cols)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			DP_cell cell = table[i][j];
			printf("(%d)-(%d)-(%d)\t", cell.insertionScore, cell.substitutionScore, cell.deletionScore);
		}
		printf("\n");
	}

}

FullCellList* GetMaxAdjacentCells(int row, int col, enum Direction prevDirection, DP_cell** table, int h)
{
	FullCellList* maxAdjacentSquares = init_full_cell_list();
	DP_cell* cell = malloc(sizeof(DP_cell));
	cell->deletionScore = table[row][col].deletionScore;
	cell->insertionScore = table[row][col].insertionScore;
	cell->substitutionScore = table[row][col].substitutionScore;
	if (prevDirection == left)
	{
		cell->deletionScore += h;
		cell->substitutionScore += h;
	}
	if (prevDirection == up)
	{
		cell->insertionScore += h;
		cell->substitutionScore += h;
	}
	const int max = GetCellMax(cell);

	if (row == 0 && col == 0)
		return init_full_cell_list();
	if (row == 0)
	{
		DP_CellFull* cell = malloc(sizeof(DP_CellFull));
		cell->cell = &table[row][col - 1];
		cell->col = col - 1;
		cell->row = row;
		cell->max = max;
		insert_cell(maxAdjacentSquares, cell);

		insert_cell(maxAdjacentSquares, cell);
		return maxAdjacentSquares;
	}
	if (col == 0)
	{
		DP_CellFull* cell = malloc(sizeof(DP_CellFull));
		cell->cell = &table[row - 1][col];
		cell->col = col;
		cell->row = row - 1;
		cell->max = max;
		insert_cell(maxAdjacentSquares, cell);
		return maxAdjacentSquares;
	}
	if (cell->deletionScore == max)
	{
		DP_CellFull* cell = malloc(sizeof(DP_CellFull));
		cell->cell = &table[row - 1][col];
		cell->col = col;
		cell->row = row - 1;
		cell->max = max;
		insert_cell(maxAdjacentSquares, cell);
	}
	if (cell->insertionScore == max)
	{
		DP_CellFull* cell = malloc(sizeof(DP_CellFull));
		cell->cell = &table[row][col - 1];
		cell->col = col - 1;
		cell->row = row;
		cell->max = max;
		insert_cell(maxAdjacentSquares, cell);
	}
	if (cell->substitutionScore == max)
	{
		DP_CellFull* cell = malloc(sizeof(DP_CellFull));
		cell->cell = &table[row - 1][col - 1];
		cell->col = col - 1;
		cell->row = row - 1;
		cell->max = max;
		insert_cell(maxAdjacentSquares, cell);
	}

	return maxAdjacentSquares;
}

int TraceBackGlobalLean(int row, int col, DP_cell** table, int h)
{
	DP_CellFull* mainMaxCell = malloc(sizeof(DP_CellFull));
	mainMaxCell->max = -1;
	int maxCellSubs = 0;
	enum Direction prevDirection = diag;
	do
	{
		const DP_CellFull* maxCell = GetMaxAdjacentCells(row, col, prevDirection, table, h)->pHead;
		if (maxCell->max > mainMaxCell->max)
		{
			mainMaxCell = maxCell;
			maxCellSubs = 0;
		}

		if (maxCell->row < row && maxCell->col < col)
		{
			//substitution
			prevDirection = diag;
			maxCellSubs++;
		}
		else if (maxCell->row < row)
		{
			//deletion
			prevDirection = up;
		}
		else
		{
			//insertion
			prevDirection = left;
		}
		row = maxCell->row;
		col = maxCell->col;
		//AddPointsToAlignment(row, col, alignment); we dont care anymore
	} while (row != 0 || col != 0);

	return maxCellSubs;
}

int TraceBackGlobal(int row, int col, char* s1, char* s2, DP_cell** table, int h)
{
	DP_CellFull* mainMaxCell = malloc(sizeof(DP_CellFull));
	mainMaxCell->max = -1;
	int maxCellSubs = 0;
	char* s1Final = malloc(sizeof(char) * (row+1));
	int s1FinalPos = row;
	char* s2Final = malloc(sizeof(char) * (col+1));
	int s2FinalPos = col;
	enum Direction prevDirection = diag;
	do
	{
		const DP_CellFull* maxCell = GetMaxAdjacentCells(row, col, prevDirection, table, h)->pHead;
		if (maxCell->max > mainMaxCell->max)
		{
			mainMaxCell = maxCell;
			maxCellSubs = 0;
		}
		
		if (maxCell->row < row && maxCell->col < col)
		{
			//substitution
			s1Final[s1FinalPos--] = s1[row - 1];
			s2Final[s2FinalPos--] = s2[col - 1];
			prevDirection = diag;
			maxCellSubs++;
		}
		else if (maxCell->row < row)
		{
			//deletion
			s1Final[s1FinalPos--] = s1[row - 1];
			s2Final[s2FinalPos--] = '-';
			prevDirection = up;
		}
		else
		{
			//insertion
			s1Final[s1FinalPos--] = '-';
			s2Final[s2FinalPos--] = s2[col - 1];
			prevDirection = left;
		}
		row = maxCell->row;
		col = maxCell->col;
		//AddPointsToAlignment(row, col, alignment); we dont care anymore
	} while (row != 0 || col != 0);

	return maxCellSubs;
}
