
int maxProduct(int* nums, int numsSize)
{
	int max = nums[0];
	int ret = 0;
	int *dpPos = malloc(sizeof(int)*numsSize);
	int *dpNeg = malloc(sizeof(int)*numsSize);

	memcpy(dpPos, nums, sizeof(int)*numsSize);
	memcpy(dpNeg, nums, sizeof(int)*numsSize);    
	for (int i = 1; i < numsSize; i++)
	{
		int tmp1 = nums[i]*dpPos[i-1];
		int tmp2 = nums[i]*dpNeg[i-1];        
		if (tmp1 > tmp2)
		{
			dpPos[i] = nums[i] > tmp1 ? nums[i] : tmp1;
			dpNeg[i] = nums[i] < tmp2 ? nums[i] : tmp2;
		} else
		{
			dpPos[i] = nums[i] > tmp2 ? nums[i] : tmp2;
			dpNeg[i] = nums[i] < tmp1 ? nums[i] : tmp1;
		}

		max = max > dpPos[i] ? max :dpPos[i];
	}

	free(dpPos);
	free(dpNeg);
	return max;
}

