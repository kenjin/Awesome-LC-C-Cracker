/**

53. Maximum Subarray [E]
- https://leetcode.com/problems/maximum-subarray/

 */

int maxSubArray(int* nums, int numsSize)
{
	/*
	 * nums[i] means the max sum of contiguous subarray end with i
	 *
	 * nums[i] = MAX(nums[i-1]+nums[i], nums[i-1])
	 *
	 */
	if (nums <= 0)
	{
		return 0;
	}

	int max = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		/* Update nums[i] */
		if ((nums[i-1]+nums[i]) > nums[i])
		{
			nums[i] = nums[i-1] + nums[i];
		}
		max = (nums[i] > max ? nums[i] : max);
	}

	return max;
}
