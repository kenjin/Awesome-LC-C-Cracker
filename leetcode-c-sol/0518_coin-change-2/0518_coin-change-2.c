int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;
	return n1-n2;
}

int change(int amount, int* coins, int coinsSize)
{
	qsort(coins, coinsSize, sizeof(int), compare);
	int *dp = calloc(amount+1, sizeof(int));
	dp[0] = 1;
	for (int i = 0; i < coinsSize; i++)
	{
		dp[0] = 1;
		for (int cur = 1; cur <= amount; cur++)
		{

			if (cur < coins[i])
			{
				continue;
			}              
			dp[cur] += dp[cur-coins[i]];
		}

	}

	int ret = dp[amount];
	free(dp);    
	return ret;
}

