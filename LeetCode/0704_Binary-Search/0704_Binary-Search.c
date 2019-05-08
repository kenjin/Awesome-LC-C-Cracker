/**

704. Binary Search [E]

Ref: https://leetcode.com/problems/binary-search/

*/

int search(int* nums, int numsSize, int target)
{
	int head = 0;
	int tail = numsSize-1;
	while (head <= tail)
	{
		int index = ((head+tail)/2);
		if (target == nums[index])
		{
			return index;
		} else if (nums[index] > target)
		{
			tail = index-1;
		} else
		{
			head = index+1;
		}
	}
	return -1;
}
