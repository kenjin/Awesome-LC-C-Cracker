
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize)
{
	int *ret = malloc(sizeof(int)*numsSize);
	int ctr = 0;
	for (int i = 0; i < numsSize; i++)
	{        
		int cur = abs(nums[i])-1;
		if (nums[cur] < 0)
		{
			ret[ctr] = cur+1;
			ctr++;
			continue;
		}

		nums[cur] *= -1;
	}

	*returnSize = ctr;
	return ret;
}

