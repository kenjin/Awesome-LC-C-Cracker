
bool canPartition(int* nums, int numsSize)
{
	int halfSum = 0;
	for (int i = 0; i < numsSize; i++)
	{
		halfSum += nums[i];
	}

	if (halfSum % 2 != 0)
	{
		return false;
	}

	halfSum /= 2;    
	int *dp = calloc(halfSum+1, sizeof(int));
	dp[0] = 1;
	for (int x = 0; x < numsSize; x++)
	{
		for (int i = halfSum; i >= nums[x]; i--)
		{
			dp[i] = dp[i] || dp[i-nums[x]];            
		}
	}

	int ret = dp[halfSum];
	free(dp);
	return ret;
}

