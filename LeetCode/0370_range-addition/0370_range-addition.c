
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getModifiedArray(int length, int** updates, int updatesSize, int* updatesColSize, int* returnSize)
{
	int *ret = calloc(length, sizeof(int));
	*returnSize = length;

	for (int i = 0; i < updatesSize; i++)
	{
		int head = updates[i][0];
		int tail = updates[i][1] + 1;
		ret[head] += updates[i][2];
		if (tail < length)
		{
			ret[tail] -= updates[i][2];
		}
	}

	for (int i = 1; i < length; i++)
	{
		ret[i] += ret[i-1];
	}
	return ret;
}

