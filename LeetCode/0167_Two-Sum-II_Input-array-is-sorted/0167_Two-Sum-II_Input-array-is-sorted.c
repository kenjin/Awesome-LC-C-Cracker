/**

167. Two Sum II - Input array is sorted [E]
Ref: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:
Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.

Example:
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]

Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.

 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
	int head = 0;
	int tail = numbersSize-1;

	while (1)
	{
		if ((numbers[head]+numbers[tail]) > target)
		{
			tail--;
		} else if ((numbers[head]+numbers[tail]) < target)
		{
			head++;
		} else /* (numbers[head]+numbers[tail]) == target */
		{
			int *ret = malloc(sizeof(int)*2);
			ret[0] = head+1;
			ret[1] = tail+1;
			*returnSize = 2;
			return ret;
		}
	}

	return NULL;
}
