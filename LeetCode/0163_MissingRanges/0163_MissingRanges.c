/*
163. Missing Ranges [Medium]

Given a sorted integer array nums, where the range of elements are in 
the inclusive range [lower, upper], return its missing ranges.

Example:

Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
Output: ["2", "4->49", "51->74", "76->99"]

 */

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findMissingRanges(int* nums, int numsSize, int lower, int upper, int* returnSize) {     
	int i;
	char **str; /* -2,147,483,648 ~ 2,147,483,647: len=23 */
	str = (char **)malloc(sizeof(char *)*(numsSize+2)); /* number of array */
	for (i = 0; i < (numsSize+2); i++)
	{        
		str[i] = (char *)malloc(sizeof(char)*24); /* MAX string 23 + '\0' */
	}
	*returnSize = 0;

	long *newNums = malloc(sizeof(long) * (numsSize+2));                    
	newNums[0] = (long)lower;
	newNums[numsSize+1] = (long)upper;
	for (i = 0; i < numsSize; i++)
	{
		newNums[i+1] = (long)nums[i];
	}

	for (i = 1; i < numsSize+2; i++)
	{
		/* first element is lower */
		if ( i-1 == 0 && newNums[i-1] == lower)
		{
			/*
				minus 1 to count "lower" as the missing value. 
				EX: [3, 5, 75]  lower = 0, upper = 99
				=> newNums = [0, 3, 5, 75, 99]
				              ^
				=> "0->3" instead of "1->3" 
			*/
			newNums[i-1] = newNums[i-1] - 1;
		}        
		/* last element is upper */
		if ( i == numsSize + 1 && newNums[i] == upper)
		{
			/* 
				plus 1 to count "upper" as the missing value. 
				EX: [3, 5, 75]  lower = 0, upper = 99
				=> newNums = [0, 3, 5, 75, 99]
				                           ^
				=> "75->99" instead of "75->98"
			*/
			newNums[i] = newNums[i] + 1;
		}

		if ((newNums[i] - newNums[i-1]) == 2)
		{
			sprintf(str[*returnSize], "%d", newNums[i]-1);
			*returnSize = *returnSize +1;            
		} else if ((newNums[i] - newNums[i-1]) > 2)
		{
			sprintf(str[*returnSize], "%d->%d", newNums[i-1] + 1, newNums[i]-1);
			*returnSize = *returnSize +1;            
		}
	}

	return str;
}
