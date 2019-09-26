
int compare(const void *a, const void *b)
{
	int *n1 = *(int **)a;
	int *n2 = *(int **)b;

	return (n1[0] == n2[0] ? n1[1]-n2[1] : n2[0]-n1[0]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes)
{
	if (peopleSize == 0)
	{
		*returnSize = 0;
		return people;
	}

	// Allocate return variables
	int **ret = calloc(peopleSize, sizeof(int *));
	*returnColumnSizes = malloc(sizeof(int)*peopleSize);        
	for (int i = 0; i < peopleSize; i++)
	{
		(*returnColumnSizes)[i] = 2;
	}

	// Sort by height from tall to small
	qsort(people, peopleSize, sizeof(int *), compare);

	// Fill the answer
	for (int i = 0; i < peopleSize; i++)
	{     
		int *replace = people[i];
		int chkIdx = people[i][1];
		while (ret[chkIdx] != NULL)
		{
			int *tmp = ret[chkIdx];    
			ret[chkIdx] = replace;
			replace = tmp;
			chkIdx++;
		}
		ret[chkIdx] = replace;
	}

	*returnSize = peopleSize;
	return ret;
}


