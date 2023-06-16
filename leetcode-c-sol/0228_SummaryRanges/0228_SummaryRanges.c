/**
228. Summary Ranges [Medium]

Given a sorted integer array without duplicates, return the summary of 
its ranges.

Example 1:

Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
Example 2:

Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.

*/


/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {

	if (numsSize == 0)
	{
		*returnSize = 0;
		return NULL;
	}

	char **ret = malloc(sizeof(char *)*numsSize);
	*returnSize = 0;
	for (int x = 0; x < numsSize; x++)
	{
		ret[x] = calloc(25, sizeof(char));
	}

	int continuousStartIdx = -1;
	int i;
	if (numsSize == 1)
	{
		*returnSize = 1;
		sprintf(ret[0], "%d", nums[0]);
		return ret;
	}
	for (i = 1; i < numsSize; i++)
	{
		/*	continous case
			Don't use "if(nums[i] - nums[i-1] == 1)" to avoid integer overflow
		 */
		if (nums[i] == nums[i-1] + 1)
		{
			if (continuousStartIdx == -1)
			{
				/* set continous index */
				continuousStartIdx = i-1;                
			}
		} else /* Sorted int array without duplicates */
		{            
			if (continuousStartIdx != -1)
			{
				sprintf(ret[*returnSize],"%d->%d", nums[continuousStartIdx], nums[i-1]);
				*returnSize += 1;
				/* reset continous index */
				continuousStartIdx = -1;
			} else /* no continuous nums beore */
			{
				sprintf(ret[*returnSize],"%d", nums[i-1]);
				*returnSize += 1;
			}            
		}

		/* The end of the array */
		if (i == (numsSize-1))
		{
			if (continuousStartIdx != -1)
			{
				sprintf(ret[*returnSize],"%d->%d", nums[continuousStartIdx], nums[i]);
				*returnSize += 1;            
			} else
			{
				sprintf(ret[*returnSize],"%d", nums[i]);
				*returnSize += 1;
			}
		}
	}

	return ret;
}
