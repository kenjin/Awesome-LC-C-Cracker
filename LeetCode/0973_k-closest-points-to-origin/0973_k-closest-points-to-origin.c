int compare(const void *a, const void *b)
{
	const int *n1 = *(int **)a;
	const int *n2 = *(int **)b;

	return (n1[1] - n2[1]);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int K, int* returnSize, int** returnColumnSizes)
{
	// data[X][0]: points index
	// data[X][1]: euclidean distance
	int **data = calloc(pointsSize, sizeof(int *));
	for (int i = 0; i < pointsSize; i++)
	{
		data[i] = malloc(sizeof(int)*2);
		data[i][0] = i;
		data[i][1] = (points[i][0])*(points[i][0]) + (points[i][1])*(points[i][1]);
	}
	// sort via the distance
	qsort(data, pointsSize, sizeof(int *), compare);

	*returnSize = K;
	int **ret = malloc(sizeof(int*)*K);
	*returnColumnSizes = malloc(sizeof(int)*K);
	for (int i = 0; i < K; i++)
	{
		(*returnColumnSizes)[i] = 2;
		ret[i] = malloc(sizeof(int)*2);
		int cur_idx = data[i][0];
		ret[i][0] = points[cur_idx][0];
		ret[i][1] = points[cur_idx][1];
		free(data[i]);
	}

	free(data);
	return ret;
}
