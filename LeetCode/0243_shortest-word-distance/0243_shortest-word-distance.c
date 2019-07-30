
int shortestDistance(char ** words, int wordsSize, char * word1, char * word2)
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

	return ret;
}

