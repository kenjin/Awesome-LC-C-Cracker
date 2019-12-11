
bool find132pattern(int* nums, int numsSize)
{

	for (int k = 1; k < numsSize-1; k++)
	{
		int i, found = 0;
		int min = nums[0], max = nums[numsSize-1];
		for (i = 0; i < k; i++)
		{
			if (nums[i] < nums[k])
			{                
				min = (min < nums[i] ? min : nums[i]);
				found = 1;
			}
		}

		if (!found)
		{
			continue;
		}

		for (int j = k+1; j < numsSize; j++)
		{
			if (nums[j] > min && nums[j] < nums[k])
			{
				return true;
			}            
		}
	}

	return false;
}

