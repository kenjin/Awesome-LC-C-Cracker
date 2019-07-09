bool findBreak(char **dp, int baseIdx, int size)
{
	if (baseIdx >= size)
	{
		return true;
	}
	for (int i = 0; i < size; i++)
	{
		if (dp[baseIdx][i])
		{
			if (findBreak(dp, i+1, size))
			{
				return true;
			}
		}
		/* key ! */
		dp[baseIdx][i] = 0;
	}
	return false;
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
	int len = strlen(s);
	// dp[i][j] - indicate that string index i to j can become a word break or not
	char **dp = calloc(len, sizeof(char*));
	for (int i = 0; i < len; i++)
	{
		dp[i] = calloc(len, sizeof(char));
	}

	for (int i = 0; i < wordDictSize; i++)
	{        
		char *tmp = strstr(s, wordDict[i]);
		while (tmp != NULL)
		{            
			int start = tmp - s;
			int end = start + strlen(wordDict[i]) - 1;
			dp[start][end] = 1;
			// continue to find from the next char
			tmp = strstr(&(s[start+1]), wordDict[i]);
		}
	}

	bool ret = findBreak(dp, 0, len);    
	for (int i = 0; i < len; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return ret;
}


