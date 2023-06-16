#define IS_VALID_NUM(rArr, cArr, bArr, row, col, box, offset) \
	(       \
			!(rArr[row] & (0x1L << offset)) && \
			!(cArr[col] & (0x1L << offset)) && \
			!(bArr[box] & (0x1L << offset)) \
	)

#define FILL_NUM(rArr, cArr, bArr, row, col, box, offset) \
{       \
	rArr[row] |= 0x1L << offset; \
	cArr[col] |= 0x1L << offset; \
	bArr[box] |= 0x1L << offset; \
}

#define RESET_NUM(rArr, cArr, bArr, row, col, box, offset) \
{       \
	rArr[row] &= ~(0x1L << offset); \
	cArr[col] &= ~(0x1L << offset); \
	bArr[box] &= ~(0x1L << offset); \
}

bool solveSudokuHelper(char **board, long *rowDone, long *colDone, long *boxDone, int row, int col)
{    
	if (row == 9)
	{
		return true;
	}

	if (col >= 9)
	{
		return solveSudokuHelper(board, rowDone, colDone, boxDone, row+1, 0);
	}

	if (board[row][col] != '.')
	{
		return solveSudokuHelper(board, rowDone, colDone, boxDone, row, col+1);
	}

	for (int i = 0; i < 9; i++)
	{        
		int boxIdx = (row/3)*3 + col/3;        
		if (IS_VALID_NUM(rowDone, colDone, boxDone, row, col, boxIdx, i))
		{
			FILL_NUM(rowDone, colDone, boxDone, row, col, boxIdx, i);
			board[row][col] = i + '1';

			if (solveSudokuHelper(board, rowDone, colDone, boxDone, row, col+1))
			{
				return true;                
			}

			RESET_NUM(rowDone, colDone, boxDone, row, col, boxIdx, i);           
			board[row][col] = '.';
		}        
	}

	return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
	long rowDone[9] = {0};
	long colDone[9] = {0};
	long boxDone[9] = {0};

	// Update the filled number
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (board[x][y] != '.')
			{
				int boxIdx = (x/3)*3 + y/3;                
				FILL_NUM(rowDone, colDone, boxDone, x, y, boxIdx, board[x][y] - '1');
			}
		}        
	}
	// Recursive fill the answer
	solveSudokuHelper(board, rowDone, colDone, boxDone, 0, 0);
}

