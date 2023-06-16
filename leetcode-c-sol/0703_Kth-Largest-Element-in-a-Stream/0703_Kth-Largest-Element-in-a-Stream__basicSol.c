typedef struct 
{
	int k;
	int s_size;
	int *s;
} KthLargest;

int compare(const void *a, const void *b)
{
	int *n1 = (int *)a;
	int *n2 = (int *)b;
	return *n1 - *n2;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) 
{
	KthLargest *obj = malloc(sizeof(KthLargest));
	qsort(nums, numsSize, sizeof(int), compare);
	obj->k = k;    
	obj->s = malloc(sizeof(int)*k);
	if (numsSize < k)
	{
		memcpy(obj->s, nums, sizeof(int)*numsSize);
	} else
	{
		memcpy(obj->s, &nums[numsSize-k], sizeof(int)*k);
	}
	obj->s_size = (numsSize < k) ? numsSize : k;

	return obj;
}

void adjustArray(int *s, int size)
{
	for (int i = 1; i < size; i++)
	{
		if (s[i] < s[i-1])
		{
			int tmp = s[i];
			s[i] = s[i-1];
			s[i-1] = tmp;
		}
	}
}

int kthLargestAdd(KthLargest* obj, int val) 
{ 
	if (obj->s_size < obj->k)
	{
		obj->s[obj->s_size] = val;
		obj->s_size++;
		adjustArray(obj->s, obj->s_size);

	} else
	{
		if (val > obj->s[0])
		{
			obj->s[0] = val;
			adjustArray(obj->s, obj->s_size);
		}
	}
	return obj->s[0];
}

void kthLargestFree(KthLargest* obj) 
{
	free(obj->s);
	free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);

 * kthLargestFree(obj);
 */
