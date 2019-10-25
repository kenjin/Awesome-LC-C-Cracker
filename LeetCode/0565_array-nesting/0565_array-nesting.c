
int arrayNesting(int* nums, int numsSize)
{
	int *visited = calloc(numsSize, sizeof(int));
	int ret = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (visited[i])
		{
			continue;
		}

		visited[i] = 1;
		int cur = i, ctr = 1;        
		cur = nums[i];
		while (i != cur)
		{
			visited[cur] = 1;
			cur = nums[cur];
			ctr++;
		}

		ret = ret > ctr ? ret : ctr;
	}

	free(visited);
	return ret;
}

