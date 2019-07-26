
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize)
{  
	for (int i = 0; i < numsSize; i++)
	{
		int cur = abs(nums[i]);
		if (nums[cur-1] > 0)
		{
			nums[cur-1] *= -1;
		}    
	}

	int *ret = malloc(sizeof(int)*numsSize);
	int ctr = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] > 0)
		{
			ret[ctr] = i+1;
			ctr++;
		}
	}
	*returnSize = ctr;
	return ret;    
}

