/**

209. Minimum Size Subarray Sum [M]
Ref: https://leetcode.com/problems/minimum-size-subarray-sum/


Given an array of n positive integers and a positive integer s, find the
minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example: 
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2

Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n). 

 */

int minSubArrayLen(int s, int* nums, int numsSize)
{
	int head = 0;
	int tail = 0;
	int minRes = numsSize+1;
	int sum = 0;
	while (tail < numsSize)
	{        
		while (sum < s && tail < numsSize)
		{
			sum += nums[tail];
			tail++;
		}

		while (sum >= s)
		{
			if ((tail-head) < minRes)
			{
				minRes = (tail-head);
			}
			sum -= nums[head];
			head++;
		}
	}

	return ((numsSize+1) == minRes) ? 0 : minRes;
}
