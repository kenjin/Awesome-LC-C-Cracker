typedef struct
{
	int *coordinate;
	int dist;
} DATA;

int compare(const void *a, const void *b)
{
	DATA d1 = *(DATA *)a;
	DATA d2 = *(DATA *)b;
	return d1.dist - d2.dist;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allCellsDistOrder(int R, int C, int r0, int c0, int* returnSize, int** returnColumnSizes)
{
	DATA *d = malloc(sizeof(DATA)*R*C);
	int **ret = malloc(sizeof(int *)*R*C);
	*returnSize = R*C;
	*returnColumnSizes = malloc(sizeof(int)*R*C);

	int ctr = 0;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			d[ctr].coordinate = malloc(sizeof(int)*2);            
			d[ctr].coordinate[0] = i;
			d[ctr].coordinate[1] = j;
			d[ctr].dist = abs(i-r0) + abs(j-c0);
			ctr++;
		}
	}

	qsort(d, R*C, sizeof(DATA), compare);
	for (int i = 0; i < R*C; i++)
	{
		ret[i] = d[i].coordinate;
		(*returnColumnSizes)[i] = 2;
	}

	free(d);
	return ret;
}

