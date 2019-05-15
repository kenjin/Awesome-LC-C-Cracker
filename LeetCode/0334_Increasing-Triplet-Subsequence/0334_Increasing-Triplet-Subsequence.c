/**

334. Increasing Triplet Subsequence [M]
Ref: https://leetcode.com/problems/increasing-triplet-subsequence/

 */

bool increasingTriplet(int* nums, int numsSize)
{
	int i = INT_MAX;
	int j = INT_MAX;

	for (int x = 0; x < numsSize; x++)
	{
		if (nums[x] <= i)
		{
			i = nums[x];
		} else if (nums[x] <= j)
		{
			j = nums[x];
		} else
		{
			return true;
		}
	}

	return false;
}
