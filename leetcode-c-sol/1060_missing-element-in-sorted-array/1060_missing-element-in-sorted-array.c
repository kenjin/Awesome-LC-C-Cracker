
int missingElementHelper(int *nums, int *head, int *tail, int numsSize, int k)
{    
	int mid = *head + (*tail-*head)/2;
	if (*tail-*head == 1)
	{
		return k;
	}
	int lMiss = nums[mid]-nums[*head]+1 - (mid-*head+1);

	if (lMiss < k)
	{
		*head = mid;
		return missingElementHelper(nums, head, tail, numsSize, k-lMiss);
	} else
	{
		*tail = mid;
		return missingElementHelper(nums, head, tail, numsSize, k);
	}
}

int missingElement(int* nums, int numsSize, int k)
{    
	int head = 0;
	int tail = numsSize-1;            
	int newK = missingElementHelper(nums, &head, &tail, numsSize, k);    
	int miss = nums[tail]-nums[head]+1 - (tail-head+1);

	if (miss == 0)
	{
		return nums[tail]+newK;
	} else
	{
		if (newK <= miss)
		{
			return nums[head]+newK;
		} else
		{
			return nums[tail]+(newK-miss);
		}
	}
}

