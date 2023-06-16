bool canSplit(int *nums, int numsSize, long target, int group)
{
	long sum = 0;
	int groupCtr = 0;
	for (int i = 0; i < numsSize; i++)
	{
		sum += nums[i];
		if (sum > target)
		{
			sum = nums[i];
			groupCtr++;
			if (groupCtr == group)
			{
				return false;
			}
		}
	}
	return  true;
}

int splitArray(int* nums, int numsSize, int m)
{
	long head = INT_MIN, tail = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] > head)
		{
			head = nums[i];
		}
		tail += nums[i];
	}

	while (head < tail)
	{
		long mid = head + (tail-head)/2;
		// based on mid, check how many group we can split
		if (canSplit(nums, numsSize, mid, m))
		{
			tail = mid;
		} else
		{
			head = mid + 1;
		}
	}

	return (int)tail;
}
