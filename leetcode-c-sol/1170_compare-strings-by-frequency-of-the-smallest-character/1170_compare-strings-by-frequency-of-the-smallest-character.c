
void updateSet(char *s, int *set)
{    
	while (*s)
	{
		set[*s - 'a'] ++;
		s++;
	} 
}

int calFreq(int *set)
{    
	for (int x = 0; x < 26; x++)
	{
		if (set[x] != 0)
		{
			return set[x];
		}
	}

	return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numSmallerByFrequency(char ** queries, int queriesSize, char ** words, int wordsSize, int* returnSize)
{
	int *ret = calloc(queriesSize, sizeof(int));
	*returnSize = queriesSize;

	int *wordFreq = malloc(sizeof(int)*wordsSize);
	for (int i = 0; i < wordsSize; i++)
	{        
		int set[26] = {0};
		updateSet(words[i], set);
		wordFreq[i] = calFreq(set);
	}

	for (int i = 0; i < queriesSize; i++)
	{
		int set[26] = {0};
		updateSet(queries[i], set);
		int freqRet = calFreq(set);

		for (int x = 0; x < wordsSize; x++)
		{
			if (freqRet < wordFreq[x])
			{
				ret[i]++;
			}
		}
	}

	free(wordFreq);    
	return ret;
}

