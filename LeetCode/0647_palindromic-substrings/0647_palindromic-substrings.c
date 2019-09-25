
int countSubstrings(char* s)
{
	int ret = 0;
	int len = strlen(s);        
	// Init DP: update length one
	char **dp = malloc(sizeof(char *)*len);
	for (int i = 0; i < len; i++)
	{
		dp[i] = calloc(len, sizeof(char));
		dp[i][i] = 1;
		ret++;
	}
	// Init DP: update length two
	for (int i = 1; i < len; i++)
	{
		if (s[i] == s[i-1])
		{
			dp[i-1][i] = 1;
			ret++;
		}
	}
	// dp[i][j] = 1, if dp[i+1][j-1] = 1 && s[i] == s[j]  
	for (int slen = 3; slen <= len; slen++)
	{
		int i = 0, j = i+slen-1;
		while (j < len)
		{            
			if (dp[i+1][j-1] && s[i] == s[j])
			{                
				dp[i][j] = 1;
				ret++;
			}

			i++;
			j++;
		}
	}

	for (int i = 0; i < len; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return ret;
}

