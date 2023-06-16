int checkEnemy(char **grid, int **d, int gridSize, int colSize)
{
	int ret = 0;
	for (int i = 0; i < gridSize; i++)
	{
		int wIdx = 0;
		int bomb = 0;
		for (int j = 0; j < colSize; j++)
		{
			if (grid[i][j] == 'W')
			{
				// Update bomb
				for (int x = wIdx; x < j; x++)
				{
					if (grid[i][x] == '0')
					{
						d[i][x] += bomb;
					}
				}
				bomb = 0;
				wIdx = j+1;
			} else if (grid[i][j] == 'E')
			{
				bomb++;
			}                        
		}

		for (int x = wIdx; x < colSize; x++)
		{
			if (grid[i][x] == '0')
			{
				d[i][x] += bomb;
			}
		}
	}

	for (int j = 0; j < colSize; j++)
	{
		int wIdx = 0;
		int bomb = 0;
		for (int i = 0; i < gridSize; i++)
		{
			if (grid[i][j] == 'W')
			{
				// Update bomb
				for (int x = wIdx; x < i; x++)
				{
					if (grid[x][j] == '0')
					{
						d[x][j] += bomb;                        
						ret = (ret > d[x][j] ? ret : d[x][j]);
					}
				}
				bomb = 0;
				wIdx = i+1;
			} else if (grid[i][j] == 'E')
			{
				bomb++;
			}                        
		}

		for (int x = wIdx; x < gridSize; x++)
		{
			if (grid[x][j] == '0')
			{
				d[x][j] += bomb;
				ret = (ret > d[x][j] ? ret : d[x][j]);
			}
		}
	}

	return ret;
}

int maxKilledEnemies(char** grid, int gridSize, int* gridColSize)
{
	if (gridSize == 0)
	{
		return 0;
	}
	int colSize = gridColSize[0];
	int **d = malloc(sizeof(int *)*gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		d[i] = calloc(colSize, sizeof(int));
	}

	int ret = checkEnemy(grid, d, gridSize, colSize);

	for (int i = 0; i < gridSize; i++)
	{
		free(d[i]);
	}
	free(d);
	return ret;
}
