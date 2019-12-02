
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize)
{    
	int n1 = 0, n2 = 0, ctr1 = 0, ctr2 = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] == n1)
		{
			ctr1++;
		} else if (nums[i] == n2)
		{
			ctr2++;
		} else if (ctr1 == 0)
		{
			n1 = nums[i];
			ctr1 = 1;
		} else if (ctr2 == 0)
		{
			n2 = nums[i];
			ctr2 = 1;
		} else
		{
			ctr1--;
			ctr2--;
		}
	}

	ctr1 = 0;
	ctr2 = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] == n1)
		{
			ctr1++;
		} else if (nums[i] == n2)
		{
			ctr2++;
		}
	}


	int *ret = malloc(sizeof(int)*2);
	*returnSize = 0;
	if (ctr1 > numsSize/3)
	{
		ret[*returnSize] = n1;
		*returnSize += 1;
	}
	if (ctr2 > numsSize/3)
	{
		ret[*returnSize] = n2;
		*returnSize += 1;
	}

	return ret;
}

