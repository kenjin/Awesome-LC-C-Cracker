void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *nums, int head, int tail)
{
	int smallerIdx = head;
	for (int i = head; i < tail; i++)
	{
		/* pivot = nums[tail] */
		if (nums[i] < nums[tail])
		{
			swap(&(nums[i]), &(nums[smallerIdx]));                  
			smallerIdx++;
		}
	}
	swap(&(nums[tail]), &(nums[smallerIdx]));
	return smallerIdx;
}

int kth_smallest_qsort(int *nums, int head, int tail, int k)
{
	if (head > tail)
	{
		return INT_MAX;
	}

	/* pivot means the sorted position in nums, all left element is smaller than pivot and right is larger */
	int pivot = partition(nums, head, tail);

	if ((pivot+1) == k)
	{
		return nums[pivot];
	} else if ((pivot+1) < k)
	{
		return kth_smallest_qsort(nums, pivot+1, tail, k);
	} else
	{
		return kth_smallest_qsort(nums, head, pivot-1, k);
	}
}

int findKthLargest(int* nums, int numsSize, int k)
{
	/* use k_s to indicate the kth smallest element */
	int k_s = numsSize-k+1;
	return kth_smallest_qsort(nums, 0, numsSize-1, k_s);
}
