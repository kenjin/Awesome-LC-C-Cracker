
int compare(const void *a, const void *b)
{
	int *n1 = *(int **)a;
	int *n2 = *(int **)b;

	return n1[0] - n2[0];    
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
	int **ret = malloc(sizeof(int *)*intervalsSize);
	(*returnColumnSizes) = malloc(sizeof(int)*intervalsSize);
	*returnSize = 0;
	if (intervalsSize == 0)
	{
		return ret;
	}

	// Sort the intervals
	qsort(intervals, intervalsSize, sizeof(int *), compare);

	int *prev = intervals[0];
	for (int curIdx = 1; curIdx < intervalsSize; curIdx++)
	{ 
		// Find overlapping
		if (prev[1] >= intervals[curIdx][0])
		{
			prev[1] = ((prev[1] <= intervals[curIdx][1]) ? intervals[curIdx][1] : prev[1]);
		} else
		{
			ret[*returnSize] = malloc(sizeof(int)*2);
			ret[*returnSize][0] = prev[0];
			ret[*returnSize][1] = prev[1];
			(*returnColumnSizes)[*returnSize] = 2;            
			*returnSize += 1;
			// Update the previous
			prev = intervals[curIdx];
		}
	}

	// Finish prev[] off
	ret[*returnSize] = malloc(sizeof(int)*2);
	ret[*returnSize][0] = prev[0];
	ret[*returnSize][1] = prev[1];
	(*returnColumnSizes)[*returnSize] = 2;
	*returnSize += 1;    

	return ret;
}

