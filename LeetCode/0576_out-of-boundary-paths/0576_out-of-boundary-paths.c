
int findPaths(int m, int n, int N, int i, int j)
{
	int ***dp = malloc(sizeof(int**)*(N+1));
	for (int k = 0; k <= N; k++)
	{
		dp[k] = malloc(sizeof(int *)*m);
		for (int i = 0; i < m; i++)
		{
			dp[k][i] = calloc(n, sizeof(int));
		}
	}
	for (int k = 1; k <= N; k++) 
	{
		for (int x = 0; x < m; x++) 
		{
			for (int y = 0; y < n; y++) 
			{
				long tmp = 0;
				tmp += (x == 0) ? 1 : dp[k - 1][x - 1][y];
				tmp += (x == m - 1) ? 1 : dp[k - 1][x + 1][y];
				tmp += (y == 0) ? 1 : dp[k - 1][x][y - 1];
				tmp += (y == n - 1) ? 1 : dp[k - 1][x][y + 1];
				dp[k][x][y] = tmp % 1000000007;
			}
		}
	}

	int ret = dp[N][i][j];
	for (int k = 0; k <= N; k++)
	{        
		for (int i = 0; i < m; i++)
		{
			free(dp[k][i]);
		}
		free(dp[k]);
	}
	free(dp);
	return ret;
}

