
int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;
	return n1-n2;
}

int threeSumSmaller(int* nums, int numsSize, int target)
{
	int ret = 0;
	qsort(nums, numsSize, sizeof(int), compare);
	for (int i = numsSize-1; i > 1; i--)
	{
		int cur = target-nums[i];
		int head = 0;
		int tail = i-1;
		while (head < tail)
		{
			if (nums[head] + nums[tail] < cur)
			{
				ret += (tail-head);                
				head++;
			} else
			{
				tail--;
			}
		}
	}

	return ret;
}


