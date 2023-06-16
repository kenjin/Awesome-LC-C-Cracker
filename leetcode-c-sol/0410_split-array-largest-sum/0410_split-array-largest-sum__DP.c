
int splitArray(int* nums, int numsSize, int m)
{
	// dp[i][j]: answer of sub-problem, splitting
	//           nums[0]~nums[j] into "i+1" group 
	//           with largest sum
	long dp[m][numsSize];
	memset(dp, 0, sizeof(int)*m*numsSize);

	// init the splitting one group DP
	dp[0][0] = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		dp[0][i] = dp[0][i-1] + nums[i];
	}

	for (int i = 1; i < m; i++)
	{
		long sum_j = 0;
		for (int j = 0; j < numsSize; j++)
		{
			sum_j += nums[j];
			long tmpMin = sum_j;
			long tmpSum = sum_j;
			for (int k = 0; k < j; k++)
			{
				tmpSum -= nums[k];
				long tmpMax = (dp[i-1][k] > tmpSum) ? dp[i-1][k] : tmpSum;

				if (tmpMax < tmpMin)
				{
					tmpMin = tmpMax;
				}
			}
			dp[i][j] = tmpMin;
		}
	}
	return dp[m-1][numsSize-1];
}

