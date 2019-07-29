
int islandPerimeter(int** grid, int gridSize, int* gridColSize)
{
	int colSize = gridColSize[0];
	int ret = 0;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (grid[i][j])
			{
				if (i == 0 || grid[i-1][j] == 0)
				{
					ret++;
				}
				if (j == 0 || grid[i][j-1] == 0)
				{
					ret++;
				}
				if (i == gridSize-1 || grid[i+1][j] == 0)
				{
					ret++;
				}
				if (j == colSize-1 || grid[i][j+1] == 0)
				{
					ret++;
				}                                
			}
		}
	}
	return ret;
}

