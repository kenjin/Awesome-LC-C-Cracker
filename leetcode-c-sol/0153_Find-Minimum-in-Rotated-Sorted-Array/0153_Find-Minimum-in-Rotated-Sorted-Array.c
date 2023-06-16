/**
153. Find Minimum in Rotated Sorted Array [M]
Ref: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:
Input: [3,4,5,1,2]
Output: 1

Example 2:
Input: [4,5,6,7,0,1,2]
Output: 0

 */

int findMin(int* nums, int numsSize)
{
    if (numsSize == 0)
    {
        return 0;
    }

    int head = 0;
    int tail = numsSize-1;
    while (head < tail)
    {
        int pivot = head+(tail-head)/2;
        /* (head == tail) or (head = tail -1)*/
        if (head == pivot || tail == pivot)
        {
            return (nums[head] < nums[tail] ? nums[head] : nums[tail]);
        }

        if (nums[head] < nums[pivot] && nums[pivot] > nums[tail])
        {
			/* #pivot is at right
			 *
		 	 *  [3,4,5,1,2]  
		 	 *   *   *   *
		 	 *         ^
		 	 */
            head = pivot;
		} else 
		{
			/*  #pivot isat left 
			 *
			 *  [1,2,3,4,5] or [5,1,2,3,4]
			 *   *   *   *      *   *   *
			 *   ^              ^
			 */
            tail = pivot;
        }
    }
    return nums[tail];
}

