
int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void wiggleSort(int* nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), compare);

	int swapIdx = (numsSize+1)/2;
	for (int i = 1; i < numsSize; i+=2)
	{
		int tmp = nums[i];
		nums[i] = nums[swapIdx];
		nums[swapIdx] = tmp;
		swapIdx++;
	}

	return nums;
}

