
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** commonChars(char ** A, int ASize, int* returnSize)
{

	int set[26] = {0};
	int tmp[26] = {0};

	int idx, cur;
	while (A[0][idx] != '\0')
	{
		cur = A[0][idx] - 'a';
		set[cur] ++;
		idx++;
	}

	for (int i = 1; i < ASize; i++)
	{
		memset(tmp, 0, sizeof(int)*26);
		idx = 0;
		while (A[i][idx] != '\0')
		{
			cur = A[i][idx] - 'a';
			tmp[cur] ++;
			idx++;
		}

		for (int x = 0; x < 26; x++)
		{
			set[x] = set[x] <= tmp[x] ? set[x] : tmp[x];
		}
	}

	char **ret = malloc(sizeof(char *)*100);
	int ctr = 0;
	for (int x = 0; x < 26; x++)
	{
		if (set[x] > 0)
		{
			for (int y = 0; y < set[x]; y++)
			{
				ret[ctr] = calloc(2, sizeof(char));
				ret[ctr][0] = x+'a';
				ctr++;
			}
		}        
	}

	*returnSize = ctr;
	return ret;
}

