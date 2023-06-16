
void maxAreaOfIslandHelper(int **grid, int **visited, int rSize, int cSize, int x, int y, int *ret)
{
	if (x < 0 || x >= rSize || y < 0 || y >= cSize || !grid[x][y] || visited[x][y])
	{
		return;
	}

	visited[x][y] = 1;
	*ret += 1;

	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};    
	for (int i = 0; i < 4; i++)
	{        
		int chkRow = x + dir[i][0];
		int chkCol = y + dir[i][1];
		maxAreaOfIslandHelper(grid, visited, rSize, cSize, chkRow, chkCol, ret);
	}
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize)
{
	int max = 0;
	int **visited = malloc(sizeof(int *)*gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		visited[i] = calloc(gridColSize[0], sizeof(int));                                
	}

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridColSize[0]; j++)
		{
			if (grid[i][j] && !visited[i][j])
			{
				int helperRet = 0;
				maxAreaOfIslandHelper(grid, visited, gridSize, gridColSize[0], i, j, &helperRet);
				max = (max > helperRet ? max : helperRet);
			}
		}
	}

	for (int i = 0; i < gridSize; i++)
	{
		free(visited[i]);
	}
	free(visited);    
	return max;
}


