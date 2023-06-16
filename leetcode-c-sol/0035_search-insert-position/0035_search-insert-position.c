
int searchInsert(int* nums, int numsSize, int target)
{
	int head = 0;
	int tail = numsSize-1;
	while (head <= tail)
	{
		int mid = (tail-head)/2 + head;
		if (nums[mid] == target)
		{
			return mid;
		} else if (nums[mid] < target)
		{
			head = mid+1;
		} else
		{
			tail = mid-1;
		}
	}

	return head;
}

