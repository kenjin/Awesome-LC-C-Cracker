/**
287. Find the Duplicate Number [M]
Ref: https://leetcode.com/problems/find-the-duplicate-number/

Given an array nums containing n + 1 integers where each integer is 
between 1 and n (inclusive), prove that at least one duplicate number
must exist. Assume that there is only one duplicate number, find the 
duplicate one.

Example 1:
Input: [1,3,4,2,2]
Output: 2

Example 2:
Input: [3,1,3,4,2]
Output: 3

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.

 */

int findDuplicate(int* nums, int numsSize)
{
	if (numsSize == 0)
	{
		return 0;
	}

	int min = 1;
	int max = numsSize-1;    
	while (min != max)
	{
		int mid = min + (max-min)/2;
		int lCtr = 0, rCtr = 0;
		for (int i = 0; i < numsSize; i++)
		{
			/* not in current range */
			if (nums[i] < min || nums[i] > max)
			{
				continue;
			}
			/* count the number */
			if (nums[i] <= mid)
			{
				lCtr++;
			} else
			{
				rCtr++;
			}
		}
		/* Check the duplicate was occured in left or right side*/
		if ((mid-min+1) < lCtr)
		{
			max = mid;
		} else
		{
			min = mid+1;
		}
	}
	return min;
}

