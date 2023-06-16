
bool divisorGame(int N)
{
	char *dp = calloc(N+1, sizeof(char));

	if (N == 1)
	{
		return false;
	}

	dp[1] = 0;
	for (int i = 2; i <= N; i++)
	{
		for (int num = 1; num < i; num++)
		{
			if (i % num == 0 &&
					dp[i-num] == 0)
			{             
				dp[i] = 1;
				break;
			}
		}
	}

	bool ret = (dp[N] == 1 ? true : false);
	free(dp);
	return ret;
}

