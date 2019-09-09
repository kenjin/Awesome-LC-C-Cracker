int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	return n1 - n2;
}

int smallestDistancePair(int* nums, int numsSize, int k)
{
	qsort(nums, numsSize, sizeof(int), compare);

	int head = 0;
	int tail = nums[numsSize-1] - nums[0];
	while (head < tail) 
	{        
		int ctr = 0;
		int tmpHeadIdx = 0;
		int mid = head + (tail - head) / 2;

		// count the abs diff that is smaller than mid
		for (int i = 0; i < numsSize; i++) 
		{
			while (tmpHeadIdx < numsSize &&
					nums[i] - nums[tmpHeadIdx] > mid)
			{
				tmpHeadIdx++;
			}
			ctr += i - tmpHeadIdx;
		}
		if (ctr < k) 
		{
			head = mid + 1;
		} else 
		{
			tail = mid;
		}
	}

	return head;
}
