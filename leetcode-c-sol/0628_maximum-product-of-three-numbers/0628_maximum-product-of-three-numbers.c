
int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;
	return n2 - n1;
}

int maximumProduct(int* nums, int numsSize)
{
	int ret = 0;
	qsort(nums, numsSize, sizeof(int), compare);

	int ret1 = nums[0]*nums[1]*nums[2];
	int ret2 = nums[0]*nums[numsSize-2]*nums[numsSize-1];
	return ret1 > ret2 ? ret1 : ret2;
}


