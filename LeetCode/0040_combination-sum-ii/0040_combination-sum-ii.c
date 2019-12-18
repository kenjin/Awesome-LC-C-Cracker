
int sumHelper(int *candidates, int curTarget, int tail, 
		int *tmp, int tmpCtr, int sum, int target, 
		int ***ret, int* returnSize, int** returnColumnSizes)
{
	int foundIdx = -1;
	for (int i = tail; i >= 0; i--)
	{
		if ((candidates[i] > curTarget) ||
				(foundIdx != -1 && candidates[i] == candidates[foundIdx]))
		{
			continue;
		}

		tmp[tmpCtr] = candidates[i];        

		if (sum+candidates[i] == target)
		{

			*ret = realloc(*ret, sizeof(int *)*(*returnSize + 1));
			*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize + 1));

			(*ret)[*returnSize] = malloc(sizeof(int)*(tmpCtr+1));
			memcpy((*ret)[*returnSize], tmp, sizeof(int)*(tmpCtr+1));
			(*returnColumnSizes)[*returnSize] = tmpCtr + 1;

			*returnSize += 1;
			foundIdx = i;
		} else
		{
			if (-1 != sumHelper(candidates, curTarget-candidates[i], i-1, 
						tmp, tmpCtr+1, sum+candidates[i], target,
						ret, returnSize, returnColumnSizes))
			{
				foundIdx = i;
			}
		}
	}   

	return foundIdx;
}

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
	qsort(candidates, candidatesSize, sizeof(int), compare);

	int **ret = malloc(sizeof(int *));
	(*returnColumnSizes) = malloc(sizeof(int));
	*returnSize = 0;

	int *tmp = malloc(sizeof(int)*candidatesSize);
	int tmpCtr = 0;
	sumHelper(candidates, target, candidatesSize-1, 
			tmp, 0, 0, target, 
			&ret, returnSize, returnColumnSizes);

	free(tmp);    
	return ret;    
}


