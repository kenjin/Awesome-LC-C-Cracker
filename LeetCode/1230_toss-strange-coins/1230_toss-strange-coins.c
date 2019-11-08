
double probabilityOfHeads(double* prob, int probSize, int target)
{
	double **dp = malloc(sizeof(double *)*probSize);
	for (int i = 0; i < probSize; i++)
	{
		dp[i] = malloc(sizeof(double)*(target+1));
	}

	dp[0][0] = 1-prob[0];
	if (target > 0)
	{
		dp[0][1] = prob[0];
	}

	for (int i = 1; i < probSize; i++)
	{
		for (int j = 0; j <= i+1 && j <= target; j++)
		{
			if (j > 0)
			{
				dp[i][j] = dp[i-1][j]*(1-prob[i]) + dp[i-1][j-1]*prob[i];
			} else
			{
				dp[i][j] = dp[i-1][j]*(1-prob[i]);
			}
		}
	}

	double ret = dp[probSize-1][target];
	for (int i = 0; i < probSize; i++)
	{
		free(dp[i]);
	}
	free(dp);

	return ret;
}

