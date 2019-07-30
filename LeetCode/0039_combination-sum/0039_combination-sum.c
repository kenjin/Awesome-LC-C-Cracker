
void combinationSumHelper(int *num, int numSize, int *tmp, int tmpSize, int curIdx, int ***ret, int *retSize, int **retColSize, int target)
{
	if (target < 0)
	{
		return;
	}
	if (target == 0)
	{
		*ret = realloc(*ret, sizeof(int *)*(*retSize + 1));
		*retColSize = realloc(*retColSize, sizeof(int)*(*retSize + 1));
		(*ret)[*retSize] = malloc(sizeof(int)*tmpSize);
		(*retColSize)[*retSize] = tmpSize;
		memcpy((*ret)[*retSize], tmp, sizeof(int)*tmpSize);
		*retSize += 1;
	}

	for (int i = curIdx; i < numSize; i++)
	{
		tmp[tmpSize] = num[i];
		combinationSumHelper(num, numSize, tmp, tmpSize+1, i, ret, retSize, retColSize, target-num[i]);
	}

}

int compare(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;

	return *n1 - *n2;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
	qsort(candidates, candidatesSize, sizeof(int), compare);
	int maxSize = target / candidates[0] + 1;
	int *tmp = malloc(sizeof(int)*maxSize);
	int **ret = malloc(sizeof(int*));
	*returnColumnSizes = malloc(sizeof(int));
	*returnSize = 0;
	combinationSumHelper(candidates, candidatesSize, tmp, 0, 0, &ret, returnSize, returnColumnSizes, target);

	free(tmp);
	return ret;
}

