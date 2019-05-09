/**

724. Find Pivot Index [E]

Ref: https://leetcode.com/problems/find-pivot-index/

 */

int pivotIndex(int* nums, int numsSize)
{
	int sum = 0;
	for (int x = 0; x < numsSize; x++)
	{
		sum += nums[x];
	}

	int checkCurrentSum = 0;
	for (int x = 0; x < numsSize; x++)
	{
		sum -= (nums[x]);
		if (sum == checkCurrentSum)
		{
			return x;
		} else
		{
			checkCurrentSum += nums[x];
		}
	}
	return -1;
}
