#define MEM_ALLOC_UNIT      (5000)

void letterHelper(char *S, int cur, int len, char ***ret, int *retSize)
{
	if (cur == len)
	{
		if (*retSize % MEM_ALLOC_UNIT == 0)
		{
			*ret = realloc(*ret, sizeof(char *)*(*retSize + MEM_ALLOC_UNIT));
		}
		(*ret)[*retSize] = calloc(len+1, sizeof(char));
		strcpy((*ret)[*retSize], S);
		*retSize += 1;
		return;
	}

	if ('a' <= S[cur] && S[cur] <= 'z')        
	{
		S[cur] = S[cur] - 'a' + 'A';
		letterHelper(S, cur+1, len, ret, retSize);
		S[cur] = S[cur] - 'A' + 'a';
	} else if ('A' <= S[cur] && S[cur] <= 'Z')
	{
		S[cur] = S[cur] - 'A' + 'a';
		letterHelper(S, cur+1, len, ret, retSize);
		S[cur] = S[cur] - 'a' + 'A';
	}

	letterHelper(S, cur+1, len, ret, retSize);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCasePermutation(char * S, int* returnSize)
{
	char **ret = malloc(sizeof(char*));
	*returnSize = 0;
	int len = strlen(S);    
	letterHelper(S, 0, len, &ret, returnSize);
	return ret;
}

