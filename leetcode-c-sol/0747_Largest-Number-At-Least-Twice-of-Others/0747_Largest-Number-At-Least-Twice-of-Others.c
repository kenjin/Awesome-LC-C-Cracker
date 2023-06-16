/**

747. Largest Number At Least Twice of Others [E]

Ref: https://leetcode.com/problems/largest-number-at-least-twice-of-others/

*/

int dominantIndex(int* nums, int numsSize)
{
	if (numsSize == 1)
	{
		return 0;
	}

	int maxIdx = -1, secondaryIdx = -1;
	for (int i = 0; i < numsSize; i++)
	{
		if (maxIdx < 0 || nums[i] > nums[maxIdx])
		{
			maxIdx = i;
		}
	}
	for (int i = 0; i < numsSize; i++)
	{
		if (i == maxIdx)
		{
			continue;
		}
		if (secondaryIdx < 0 || nums[i] > nums[secondaryIdx])
		{
			secondaryIdx = i;
		}
	}
	return (nums[secondaryIdx]*2 <= nums[maxIdx] ? maxIdx : -1);
}
