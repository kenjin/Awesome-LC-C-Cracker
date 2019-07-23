
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char * s, char * p, int* returnSize)
{
	int alpha[26] = {0};
	int alphaCal[26] = {0};
	int pLen = strlen(p);
	int sLen = strlen(s);        
	int *ret = malloc(sizeof(int)*sLen);
	int retCtr = 0;
	*returnSize = 0;

	for (int i = 0; i < pLen; i++)
	{
		alpha[(p[i] - 'a')] += 1;
	}
	for (int i = 0; i < sLen; i++)
	{
		int curIdx = s[i] - 'a';
		if (i >= pLen)
		{
			int startIdx = s[i-pLen] - 'a';
			alphaCal[startIdx]--;
		}
		alphaCal[curIdx]++;
		if (!memcmp(alphaCal, alpha, 26*sizeof(int)))
		{
			ret[retCtr] = i - pLen + 1;
			retCtr++;
		}
	}

	*returnSize = retCtr;
	return ret;
}


