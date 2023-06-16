#define MALLOC_UNIT 5000
void strobogrammaticHelper(char ***ret, int *retCtr, int *memUnit, char *tmp, int cur, int n, char isOdd)
{
	char *nums1 = "01689";
	char *nums2 = "01986";
	if (cur == n/2)
	{
		if (isOdd)
		{
			int midIdx = n/2;
			(*ret)[*retCtr] = calloc(n+1, sizeof(char));
			(*ret)[*retCtr+1] = calloc(n+1, sizeof(char));
			(*ret)[*retCtr+2] = calloc(n+1, sizeof(char));
			memcpy((*ret)[*retCtr], tmp, sizeof(char)*n);
			memcpy((*ret)[*retCtr+1], tmp, sizeof(char)*n);
			memcpy((*ret)[*retCtr+2], tmp, sizeof(char)*n);
			(*ret)[*retCtr][midIdx] = '0';
			(*ret)[*retCtr+1][midIdx] = '1';
			(*ret)[*retCtr+2][midIdx] = '8';
			*retCtr += 3;
			*memUnit += 3;
		} else
		{
			(*ret)[*retCtr] = calloc(n+1, sizeof(char));
			memcpy((*ret)[*retCtr], tmp, sizeof(char)*n);
			*retCtr += 1;
			*memUnit += 1;
		}

		if (*memUnit + 3 >= MALLOC_UNIT)
		{
			*ret = realloc(*ret, sizeof(char *)*(*retCtr+MALLOC_UNIT));
			*memUnit = 0;            
		}
		return ;
	}

	for (int i = 0; i < 5; i++)
	{
		// string can not start from '0'
		if (cur == 0 && i == 0)
		{
			continue;
		}
		tmp[cur] = nums1[i];
		tmp[n-cur-1] = nums2[i];
		strobogrammaticHelper(ret, retCtr, memUnit, tmp, cur+1, n, isOdd);
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findStrobogrammatic(int n, int* returnSize)
{
	int **ret = malloc(sizeof(char*)*MALLOC_UNIT);
	*returnSize = 0;

	char *tmp = calloc(n+1, sizeof(char));
	char isOdd = ((n & 0x1) == 0x1 ? 1 : 0);
	int memUnit = 0;
	strobogrammaticHelper(&ret, returnSize, &memUnit, tmp, 0, n, isOdd);

	free(tmp);
	return ret;
}


