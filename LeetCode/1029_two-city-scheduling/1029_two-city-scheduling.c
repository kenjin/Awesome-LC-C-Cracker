
int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize)
{
	int sum = 0;
	for (int i = 0; i < costsSize; i++)
	{
		sum += costs[i][0];
	}

	int *diff = malloc(sizeof(int)*costsSize);
	for (int i = 0; i < costsSize; i++)
	{
		diff[i] = costs[i][1] - costs[i][0];
	}

	qsort(diff, costsSize, sizeof(int), compare);
	for (int i = 0; i < costsSize/2; i++)
	{
		sum += diff[i];
	}

	free(diff);
	return sum;
}

