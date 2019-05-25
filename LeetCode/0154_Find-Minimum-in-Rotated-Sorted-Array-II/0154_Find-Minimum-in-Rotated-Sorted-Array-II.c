/**
154. Find Minimum in Rotated Sorted Array II [H]

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

Example 1:
Input: [1,3,5]
Output: 1

Example 2:
Input: [2,2,2,0,1]
Output: 0

Note:
This is a follow up problem to Find Minimum in Rotated Sorted Array.
Would allow duplicates affect the run-time complexity? How and why?

 */

int findMin(int* nums, int numsSize)
{
	int head = 0;
	int tail = numsSize-1;

	while (head < tail)
	{
		int mid = head + (tail-head)/2;
		if (nums[mid] == nums[tail])
		{
			tail--;
		} else if (nums[mid] > nums[tail])
		{
			head = mid+1;
		} else
		{
			tail = mid;
		}
	}
	return nums[head];
}

