
void crushBoard(int** board, int boardSize, int colSize, int **chk)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (chk[i][j])
			{
				board[i][j] = 0;
				// Clear checking info
				chk[i][j] = 0;
			}
		}
	}

	int *tmp = malloc(sizeof(int)*boardSize);
	for (int j = 0; j < colSize; j++)
	{
		memset(tmp, 0, sizeof(int)*boardSize);
		int tmpCtr = boardSize-1;
		for (int i = boardSize-1; i >=0; i--)
		{
			if (board[i][j] != 0)
			{
				tmp[tmpCtr] = board[i][j];
				tmpCtr--;
			}
		}

		for (int i = boardSize-1; i >=0; i--)
		{
			if (tmp[i])
			{
				board[i][j] = tmp[i];                
			} else
			{
				board[i][j] = 0;
			}
		}

	}

	free(tmp);
}

void updateCrushInfo(int **chk, int isRow, int base, int start, int end)
{
	if (isRow)
	{
		for (int i = start; i <= end; i++)
		{
			chk[base][i] = 1;
		}
	} else
	{
		for (int i = start; i <= end; i++)
		{
			chk[i][base] = 1;
		}
	}
}

int candyCrushHelper(int** board, int boardSize, int colSize, int **chk)
{
	int found = 0;
	int ctr = 1;

	// Check Row
	for (int i = 0; i < boardSize; i++)
	{
		int pre = board[i][0];
		ctr = 1;
		for (int j = 1; j < colSize; j++)
		{
			if (board[i][j] == pre && board[i][j] != 0)
			{
				ctr++;
			} else
			{
				if (ctr >= 3)
				{
					updateCrushInfo(chk, 1, i, j-ctr, j-1);
					found = 1;
				}

				ctr = 1;
			}

			pre = board[i][j];
		}
		if (ctr >= 3)
		{
			updateCrushInfo(chk, 1, i, colSize-ctr, colSize-1);
			found = 1;
		}
	}
	// Check Column
	for (int j = 0; j < colSize; j++)    
	{
		int pre = board[0][j];
		ctr = 1;
		for (int i = 1; i < boardSize; i++)
		{
			if (board[i][j] == pre && board[i][j] != 0)
			{
				ctr++;
			} else
			{
				if (ctr >= 3)
				{
					updateCrushInfo(chk, 0, j, i-ctr, i-1);
					found = 1;
				}
				ctr = 1;
			}

			pre = board[i][j];
		}
		if (ctr >= 3)
		{
			updateCrushInfo(chk, 0, j, boardSize-ctr, boardSize-1);
			found = 1;
		}
	}
	return found;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** candyCrush(int** board, int boardSize, int* boardColSize, int* returnSize, int** returnColumnSizes)
{
	int colSize = boardColSize[0];
	int **chk = malloc(sizeof(int *)*boardSize);
	for (int i = 0; i < boardSize; i++)
	{
		chk[i] = calloc(colSize, sizeof(int));        
	}

	while (1)
	{
		if (!candyCrushHelper(board, boardSize, colSize, chk))       
		{
			break;
		}
		// Crush board and clear the checking info
		crushBoard(board, boardSize, colSize, chk);
	}

	*returnSize = boardSize;
	*returnColumnSizes = malloc(sizeof(int)*boardSize);
	for (int i = 0; i < boardSize; i++)
	{
		(*returnColumnSizes)[i] = colSize;
		free(chk[i]);
	}
	free(chk);
	return board;
}


