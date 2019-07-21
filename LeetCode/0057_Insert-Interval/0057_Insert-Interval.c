int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes)
{   
	int **ret = malloc(sizeof(int*)*(intervalsSize+1));
	*returnColumnSizes = malloc(sizeof(int)*(intervalsSize+1));
	*returnSize = 0;
	char srcChk = 0, dstChk = 0;

	int i;
	while (i < intervalsSize)
	{
		int src = intervals[i][0];
		int dst = intervals[i][1];
		if (newInterval[0] < src)
		{
			ret[*returnSize] = malloc(sizeof(int)*2);            
			(*returnColumnSizes)[*returnSize] = 2;
			ret[*returnSize][0] = newInterval[0];            
			srcChk = 1;
			break;
		} else if (newInterval[0] > dst)
		{
			ret[*returnSize] = malloc(sizeof(int)*2);
			ret[*returnSize][0] = src;
			ret[*returnSize][1] = dst;
			(*returnColumnSizes)[*returnSize] = 2;
			*returnSize += 1;
			i++;
		} else /* src <= newInterval[0] <= dst*/
		{
			ret[*returnSize] = malloc(sizeof(int)*2);
			(*returnColumnSizes)[*returnSize] = 2;
			ret[*returnSize][0] = src;            
			srcChk = 1;
			break;
		}        
	}
	while (i < intervalsSize)
	{
		int src = intervals[i][0];
		int dst = intervals[i][1];
		if (newInterval[1] < src)
		{
			ret[*returnSize][1] = newInterval[1];
			*returnSize += 1;
			dstChk = 1;
			break;
		} else if (newInterval[1] > dst)
		{
			i++;
		} else /* src <= newInterval[1] <= dst*/
		{
			ret[*returnSize][1] = dst;
			*returnSize += 1;
			dstChk = 1;
			i++;
			break;
		}        
	}

	while (i < intervalsSize)
	{
		ret[*returnSize] = malloc(sizeof(int)*2);
		ret[*returnSize][0] = intervals[i][0];
		ret[*returnSize][1] = intervals[i][1];
		(*returnColumnSizes)[*returnSize] = 2;
		*returnSize += 1;
		i++;
	}

	// Tail edge Case
	if (!dstChk)
	{
		if (!srcChk)
		{
			ret[*returnSize] = malloc(sizeof(int)*2);
			ret[*returnSize][0] = newInterval[0];
			ret[*returnSize][1] = newInterval[1];
			(*returnColumnSizes)[*returnSize] = 2;
			*returnSize += 1;
		} else
		{
			ret[*returnSize][1] = newInterval[1];
			*returnSize += 1;
		}
	}

	return ret;
}
