

bool repeatedSubstringPattern(char * s)
{
	int len = strlen(s);
	int *dp = calloc(len+1, sizeof(int));
	int i = 1, j = 0;
	while (i < len)
	{
		if (s[i] == s[j])
		{
			dp[i+1] = j+1;
			i++;
			j++;
		} else if (j == 0)
		{
			i++;
		} else
		{
			j = dp[j];
		}
	}

	bool ret = (dp[len] && (dp[len] % (len - dp[len]) == 0));
	free(dp);

	return ret;
}


