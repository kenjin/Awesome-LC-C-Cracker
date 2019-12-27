typedef struct
{
	int num;
	int val;
} DATA;

int hash(int n, int modNum)
{
	if (n < 0)
	{
		return (n + INT_MAX) % modNum;
	}
	return n % modNum;
}

int findHash(DATA *d, int n, int modNum)
{
	int idx = hash(n, modNum);
	while (d[idx].val != 0)
	{
		if (d[idx].num == n)
		{
			return d[idx].val;
		}
		idx = (idx+1) % modNum;
	}
	return 0;
}

int addHash(DATA *d, int n, int modNum)
{
	int idx = hash(n, modNum);
	while (d[idx].val != 0)
	{
		if (d[idx].num == n)
		{
			break;
		}
		idx = (idx+1) % modNum;
	}

	d[idx].num = n;
	d[idx].val += 1;
	return d[idx].val;
}

int findLHS(int* nums, int numsSize)
{
	int size = numsSize+1;
	DATA *d = calloc(size, sizeof(DATA));
	int max = 0;
	for (int i = 0; i < numsSize; i++)
	{
		int f0 = addHash(d, nums[i], size);
		int f1 = findHash(d, nums[i]-1, size);                
		int f2 = findHash(d, nums[i]+1, size);
		if (f1 == 0 && f2 == 0)
		{
			continue;
		}        
		int cur = (f1 > f2 ? f1 : f2) + f0;
		max = max > cur ? max : cur;        
	}
	free(d);

	return max;
}

