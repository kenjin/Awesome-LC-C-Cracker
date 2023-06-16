
int longestPalindromeSubseq(char * s)
{
	int len = strlen(s);
	if (len == 0)
	{
		return 0;
	}

	int **dp = malloc(sizeof(int*)*len);	
	// init "len = 1" and "len = 2" cases
	dp[0] = calloc(len, sizeof(int));
	dp[0][0] = 1;
	for (int i = 1; i < len; i++)
	{
		dp[i] = calloc(len, sizeof(int));
		dp[i][i] = 1;
		dp[i-1][i] = (s[i-1] == s[i] ? 2 : 1);        
	}
	// dp
	for (int x = 2; x < len; x++)
	{
		for (int i = 0; i+x < len; i++)
		{
			int head = i;
			int tail = i+x;
			if (s[head] == s[tail])
			{
				dp[head][tail] = dp[head+1][tail-1] + 2;
			} else
			{
				int lRet = dp[head+1][tail];
				int rRet = dp[head][tail-1];				
				dp[head][tail] = lRet > rRet ? lRet : rRet;
			}
		}		
	}

	int ret = dp[0][len-1];
	for (int i = 0; i < len; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return ret;
}
