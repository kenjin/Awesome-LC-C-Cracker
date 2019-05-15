/**
78. Subsets [M]
Ref: https://leetcode.com/problems/subsets/

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:
Input: nums = [1,2,3]
Output:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]

 */

void calSubsets(int* nums, int idx, int numsSize, int *tmp, int count, int **ret, int* returnSize, int** returnColumnSizes)
{
	if (idx == numsSize)
	{
		*returnSize += 1;                        
		ret[(*returnSize)-1] = malloc(sizeof(int)*count);
		memcpy(ret[(*returnSize)-1], tmp, sizeof(int)*count);
		(*returnColumnSizes)[(*returnSize)-1] = count;            
		return;
	}
	calSubsets(nums, idx+1, numsSize, tmp, count, ret, returnSize, returnColumnSizes);
	tmp[count] = nums[idx];
	count++;
	calSubsets(nums, idx+1, numsSize, tmp, count, ret, returnSize, returnColumnSizes);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{    
	*returnSize = 0;
	double resCtr = pow(2, numsSize);
	int **ret = calloc(resCtr, sizeof(int *));
	(*returnColumnSizes) = calloc(resCtr, sizeof(int));

	int *tmp = calloc(numsSize, sizeof(int));
	calSubsets(nums, 0, numsSize, tmp, 0, ret, returnSize, returnColumnSizes);
	free(tmp);
	return ret;
}
