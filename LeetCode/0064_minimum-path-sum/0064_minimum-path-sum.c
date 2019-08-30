
int minPathSum(int** grid, int gridSize, int* gridColSize)
{
	int m = gridSize;
	int n = gridColSize[0];
	int **dp = malloc(sizeof(int *)*m);
	for (int i = 0; i < m; i++)
	{
		dp[i] = calloc(n, sizeof(int));
	}

	dp[0][0] = grid[0][0];  
	for (int sum_x_y = 1;
			sum_x_y <= (m + n - 2); /* Max Sum of row index and col index*/
			sum_x_y++)
	{
		for (int x= 0; x < m; x++)
		{                        
			int row = x;
			int col = sum_x_y - x;
			if (col < 0 || col >= n)
			{
				continue;
			}

			int tmpMin = INT_MAX;
			if (col-1 >= 0)
			{
				tmpMin = dp[row][col-1];
			}
			if (row-1 >= 0)
			{
				tmpMin = dp[row-1][col] < tmpMin ? dp[row-1][col] : tmpMin;
			}

			dp[row][col] = tmpMin + grid[row][col];
		}
	}

	int ret = dp[m-1][n-1];
	for (int i = 0; i < m; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return ret;
}

