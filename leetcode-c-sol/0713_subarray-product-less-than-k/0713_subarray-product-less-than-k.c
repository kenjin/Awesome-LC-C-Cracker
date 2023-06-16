
int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
	if (k <= 1) 
	{
		return 0;
	}

	int ret = 0, prod = 1;
	int left = 0, right = 0;
	while (right < numsSize)
	{
		prod *= nums[right];
		while (prod >= k)
		{
			prod /= nums[left];
			left++;
		}
		ret += (right - left + 1);

		right++;
	}
	return ret;
}

