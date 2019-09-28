
int findLengthOfLCIS(int* nums, int numsSize)
{
	int *dp = calloc(numsSize, sizeof(int));    
	if (numsSize == 0)
	{
		return 0;
	}

	int max = 1;
	dp[0] = 1;
	for (int i = 1; i < numsSize; i++)
	{
		dp[i] = (nums[i-1] >= nums[i] ? 1 : dp[i-1] + 1);       
		max = max > dp[i] ? max : dp[i];
	}

	free(dp);
	return max;
}

