
int findMaxLength(int* nums, int numsSize)
{
	int *sum = malloc(sizeof(int)*(numsSize*2+1));        
	for (int i = 0; i < numsSize*2+1; i++)
	{
		sum[i] = -1;
	}

	int *tmp = &(sum[numsSize]);
	int ret = 0;
	int curSum = 0;
	for (int i = 0; i < numsSize; i++)
	{
		curSum = (nums[i] == 0 ? curSum-1 : curSum+1);
		if (tmp[curSum] == -1 && curSum != 0)
		{
			tmp[curSum] = i;
			continue;
		} else
		{
			int diff = i - tmp[curSum];
			ret = ret > diff ? ret : diff;
		}
	}

	free(sum);
	return ret;
}

