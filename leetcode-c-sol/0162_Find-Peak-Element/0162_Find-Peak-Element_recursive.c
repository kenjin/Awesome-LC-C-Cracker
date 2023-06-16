
int fPE(int *n, int head, int tail, int numsSize)
{
	int mid = head + (tail-head)/2;
	if ((mid == 0 || n[mid-1] <= n[mid]) &&
		(mid == numsSize-1 || n[mid] >= n[mid+1]))
	{
		return mid;
	} else if (mid >= 0 && n[mid] < n[mid+1])
	{
		return fPE(n, mid+1, tail, numsSize);
	} else  /* n[mid] > n[mid+1] */
	{
		return fPE(n, head, mid, numsSize);
	}
}

int findPeakElement(int* nums, int numsSize)
{
	return fPE(nums, 0, numsSize-1, numsSize);
}


