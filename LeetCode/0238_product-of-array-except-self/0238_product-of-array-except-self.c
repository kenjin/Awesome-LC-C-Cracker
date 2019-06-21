int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
	int *ret = calloc(numsSize, sizeof(int));
	*returnSize = numsSize;

	for (int i = 0; i < numsSize; i++)
	{
		ret[i] = (i == 0 ? 1 : ret[i-1]*nums[i-1]);
	}

	int lastTmp = 0;
	for (int i = numsSize-1; i >= 0; i--)
	{
		lastTmp = (i == numsSize-1 ?  1 : lastTmp*nums[i+1]);
		ret[i] = ret[i]*lastTmp;
	}
	return ret;
}
