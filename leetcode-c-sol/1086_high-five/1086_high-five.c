
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** highFive(int** items, int itemsSize, int* itemsColSize, int* returnSize, int** returnColumnSizes)
{
	int **ids = malloc(sizeof(int *)*(itemsSize/5));
	for (int i = 0; i < (itemsSize/5); i++)
	{
		ids[i] = calloc(6, sizeof(int));
	}

	int maxId = 0;
	for (int i = 0; i < itemsSize; i++)
	{
		int idx = items[i][0] - 1;
		int val = items[i][1];
		maxId = idx > maxId ? idx : maxId;

		ids[idx][5] = val;
		for (int x = 5; x > 0; x--)
		{
			if (ids[idx][x-1] >= ids[idx][x])
			{
				break;
			}            
			swap(&(ids[idx][x-1]), &(ids[idx][x]));            
		}
	}

	int **ret = malloc(sizeof(int *)*(maxId+1));
	*returnColumnSizes = malloc(sizeof(int)*(maxId+1));
	for (int i = 0; i <= maxId; i++)
	{
		int sum = 0;
		for (int x = 0; x < 5; x++)
		{
			sum += ids[i][x];            
		}

		(*returnColumnSizes)[i] = 2;
		ret[i] = malloc(sizeof(int)*2);
		ret[i][0] = i + 1;                
		ret[i][1] = sum/5;
	}
	*returnSize = (maxId+1);
	return ret;
}

