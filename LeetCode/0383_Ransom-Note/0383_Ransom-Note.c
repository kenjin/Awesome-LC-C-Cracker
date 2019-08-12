
bool canConstruct(char * ransomNote, char * magazine)
{
	int *ranSet = calloc(26, sizeof(int));
	int *magSet = calloc(26, sizeof(int));

	bool ret = true;
	int idx = 0;
	while (ransomNote[idx] != '\0')
	{
		ranSet[(ransomNote[idx] - 'a')] += 1;
		idx++;
	}
	idx = 0;
	while (magazine[idx] != '\0')
	{
		magSet[(magazine[idx] - 'a')] += 1;
		idx++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (magSet[i] < ranSet[i])
		{
			ret = false;
			break;
		}
	}

	free(ranSet);
	free(magSet);

	return ret;
}

