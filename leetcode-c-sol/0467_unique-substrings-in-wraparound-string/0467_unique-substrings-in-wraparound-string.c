#define MAX(a, b) (a > b ? a : b)

int findSubstringInWraproundString(char * p)
{
	int set[26] = {0};
	int prevIdx = -1;
	int len = 0;
	while (*p)
	{
		int curIdx = *p - 'a';
		if (prevIdx >= 0 && (prevIdx+1)%26 == curIdx)
		{
			len++;
		} else
		{
			len = 1;
		}        
		set[curIdx] = MAX(set[curIdx], len);
		prevIdx = curIdx;
		p++;
	}

	int ret = 0;
	for (int i = 0; i < 26; i++)
	{
		ret += set[i];
	}
	return ret;
}

