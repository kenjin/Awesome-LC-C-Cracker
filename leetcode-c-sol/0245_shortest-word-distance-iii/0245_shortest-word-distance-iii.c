
int __shortestWordDistance_same(char ** words, int wordsSize, char * word)
{
	int *idx = malloc(sizeof(int)*wordsSize);
	int ctr = 0;

	for (int i = 0; i < wordsSize; i++)
	{
		if (!strcmp(words[i], word))
		{
			idx[ctr] = i;
			ctr++;
		}
	}

	int ret = idx[1] - idx[0];
	for (int i = 2; i < ctr; i++)
	{
		int tmp = idx[i] - idx[i-1];
		ret = (ret < tmp ? ret : tmp);
	}

	free(idx);
	return ret;
}

int __shortestWordDistance_diff(char ** words, int wordsSize, char * word1, char * word2)
{
	int *idx1 = malloc(sizeof(int)*wordsSize);
	int *idx2 = malloc(sizeof(int)*wordsSize);
	int ctr1 = 0, ctr2 = 0;

	for (int i = 0; i < wordsSize; i++)
	{
		if (!strcmp(words[i], word1))
		{
			idx1[ctr1] = i;
			ctr1++;
		}
		if (!strcmp(words[i], word2))
		{
			idx2[ctr2] = i;
			ctr2++;
		}
	}

	int ret = INT_MAX;
	int i = 0, j = 0;    
	while (i < ctr1 && j < ctr2)
	{
		int tmp = abs(idx1[i]-idx2[j]);
		ret = (tmp < ret) ? tmp : ret;

		if (idx1[i] < idx2[j])
		{
			i++;
		} else
		{
			j++;
		}                
	}

	free(idx1);
	free(idx2);
	return ret;
}

int shortestWordDistance(char ** words, int wordsSize, char * word1, char * word2)
{
	if (!strcmp(word1, word2))
	{
		return __shortestWordDistance_same(words, wordsSize, word1);
	} else
	{
		return __shortestWordDistance_diff(words, wordsSize, word1, word2);
	}
}

