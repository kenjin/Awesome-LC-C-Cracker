
int lastStoneWeightII(int* stones, int stonesSize)
{
	int sum = 0;
	for (int i = 0; i < stonesSize; i++)
	{
		sum += stones[i];
	}

	char *dp = calloc(sum+1, sizeof(char));
	dp[0] = 1;

	for (int i = 0; i < stonesSize; i++)
	{
		for (int j = sum / 2; j >= stones[i]; j--)
		{
			dp[j] = dp[j] | dp[j - stones[i]];
		}
	}                    

	for (int i = sum / 2; i >= 0; i--)
	{
		if (dp[i])
		{
			return sum - i - i;
		}
	}

	return sum;
}

