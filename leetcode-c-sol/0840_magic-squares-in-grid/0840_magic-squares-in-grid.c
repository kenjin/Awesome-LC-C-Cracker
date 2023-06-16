#define VALID_IDX(r, c, rSize, cSize)  (r > 0 && r < rSize-1 && c > 0 && c < cSize-1)

bool validMagicGrid(int **grid, int row, int col)
{
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, -1}, {-1, 1}};
	int set[10] = {0};    	
	set[0] = set[5] = 1;
	for (int x = 0; x < 4; x++)
	{
		int n1 = grid[row + dir[x][0]][col + dir[x][1]];
		int n2 = grid[row - dir[x][0]][col - dir[x][1]];
		if (n1 < 10 && n2 < 10 && set[n1] == 0 && set[n2] == 0 && 
				n1 == 10 - n2)
		{
			set[n1] = 1;
			set[n2] = 1;
		} else
		{
			return false;
		}
	}    
	// Check the row and column without center point 
	for (int i = -1; i < 2; i+=2 /* ignore center point */)
	{
		if (grid[row+i][col-1] + grid[row+i][col] + grid[row+i][col+1] != 15)
		{
			return false;
		}
		if (grid[row-1][col+i] + grid[row][col+i] + grid[row+1][col+i] != 15)
		{
			return false;
		}
	}

	return true;
}

int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize)
{
	int colSize = gridColSize[0];
	int ret = 0;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (VALID_IDX(i, j, gridSize, colSize) && 
					grid[i][j] == 5)
			{             
				ret = validMagicGrid(grid, i, j) ? ret + 1 : ret;                    
			}
		}
	}

	return ret;
}

