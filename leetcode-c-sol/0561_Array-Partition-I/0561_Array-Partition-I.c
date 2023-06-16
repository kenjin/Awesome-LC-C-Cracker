/**

561. Array Partition I [E]
Ref: https://leetcode.com/problems/array-partition-i/

Given an array of 2n integers, your task is to group these integers into
n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes 
sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).

Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].

 */

int compare(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return (*n1-*n2);
}

int arrayPairSum(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), compare);
	int sum = 0;
	int head = 0;
	int tail = numsSize-2;
	while (head <= tail)
	{
		/* Head and tail at the same location */
		if (head == tail)
		{
			sum += nums[head];
			break;
		}
		sum = sum + nums[head] + nums[tail];
		head += 2;
		tail -= 2;
	}
	return sum;
}
