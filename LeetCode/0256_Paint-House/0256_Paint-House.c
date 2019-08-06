
int minCost(int** costs, int costsSize, int* costsColSize)
{
	if (costsSize == 0)
	{
		return 0;
	}

	int **dp = malloc(sizeof(int *)*costsSize);
	for (int i = 0; i < costsSize; i++)
	{
		dp[i] = calloc(3, sizeof(int));
	}

	dp[0][0] = costs[0][0];
	dp[0][1] = costs[0][1];
	dp[0][2] = costs[0][2];

	for (int i = 1; i < costsSize; i++)
	{
		dp[i][0] = (dp[i-1][1] < dp[i-1][2] ? dp[i-1][1] + costs[i][0] : dp[i-1][2] + costs[i][0]);
		dp[i][1] = (dp[i-1][0] < dp[i-1][2] ? dp[i-1][0] + costs[i][1] : dp[i-1][2] + costs[i][1]);
		dp[i][2] = (dp[i-1][0] < dp[i-1][1] ? dp[i-1][0] + costs[i][2] : dp[i-1][1] + costs[i][2]);
	}

	int ret = dp[costsSize-1][0] < dp[costsSize-1][1] ? dp[costsSize-1][0] : dp[costsSize-1][1];
	ret = ret < dp[costsSize-1][2] ? ret : dp[costsSize-1][2];

	for (int i = 0; i < costsSize; i++)
	{
		free(dp[i]);
	}
	free(dp);

	return ret;
}

