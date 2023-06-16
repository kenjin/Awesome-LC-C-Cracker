int compare(const void *a, const void *b)
{
	int n1 = *(int *)a;
	int n2 = *(int *)b;

	return n1-n2;
}

int findUnsortedSubarray(int* nums, int numsSize)
{
	int *tmp = malloc(sizeof(int)*numsSize);
	memcpy(tmp, nums, sizeof(int)*numsSize);
	qsort(tmp, numsSize, sizeof(int), compare);

	int head = 0;
	int tail = numsSize-1;

	while (head < numsSize)
	{
		if (nums[head] != tmp[head])
		{        
			break;
		}                
		head++;
	}

	while (tail >= 0)
	{
		if (nums[tail] != tmp[tail])
		{       
			break;
		}                
		tail--; 
	}

	free(tmp);
	int ret = tail-head+1;
	return ret > 0 ? ret : 0;
}

