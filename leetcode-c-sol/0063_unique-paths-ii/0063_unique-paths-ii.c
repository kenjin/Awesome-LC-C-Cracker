
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
	long **dp = malloc(sizeof(long *)*obstacleGridSize);
	int colSize = obstacleGridColSize[0];
	for (int i = 0; i < obstacleGridSize; i++)
	{
		dp[i] = calloc(colSize, sizeof(long));
	}

	dp[0][0] = !obstacleGrid[0][0];
	for (int i = 0; i < obstacleGridSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (obstacleGrid[i][j])
			{
				continue;
			}

			if (i-1 >= 0)
			{
				dp[i][j] += dp[i-1][j];
			}
			if (j-1 >= 0)
			{
				dp[i][j] += dp[i][j-1];
			}
		}
	}

	int ret = dp[obstacleGridSize-1][colSize-1];
	for (int i = 0; i < obstacleGridSize; i++)
	{
		free(dp[i]);
	}
	free(dp);

	return ret;
}

