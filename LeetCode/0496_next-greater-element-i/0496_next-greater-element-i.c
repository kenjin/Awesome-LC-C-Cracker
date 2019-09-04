typedef struct
{
	int size;
	int cur;
	int *arr;
} STACK;

typedef struct
{
	int idx;
	int val;   
} INFO;

typedef struct
{
	int size;
	int mod;
	INFO *arr;
} HASH;

int hash(HASH *obj, int key) 
{
	int r = key % obj->mod;
	return r < 0 ? r + obj->size : r;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->arr = malloc(sizeof(INFO)*(size));
	for (int x = 0; x < size; x++)
	{
		obj->arr[x].idx = -1;
	}
	return obj;
}

void addHash(HASH *ht, int key, int idx) 
{
	int index = hash(ht, key);
	while (ht->arr[index].idx != -1) 
	{
		index++;
		index %= ht->size;
	}
	ht->arr[index].idx = idx;
	ht->arr[index].val = key;
}

int findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index].idx != -1) 
	{
		if (ht->arr[index].val == target) 
		{
			return ht->arr[index].idx;
		}
		index++;
		index %= ht->size;
	}
	return -1;
}

void releaseHash(HASH *ht)
{
	free(ht->arr);
	free(ht);
}

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(int)*size);
	return obj;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, int idx)
{
	obj->cur += 1;
	obj->arr[obj->cur] = idx;
}

int stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return -1;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

int stackTop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		return -1;
	}
	return obj->arr[obj->cur];
}

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
	int *ret = malloc(sizeof(int)*nums1Size);
	*returnSize = nums1Size;
	HASH *h = createHash(nums1Size+1);
	STACK *s = stackCreate(nums2Size);

	for (int i = 0; i < nums1Size; i++)
	{
		// Set default is not exist
		ret[i] = -1;
		// Update index to hash map
		addHash(h, nums1[i], i);
	}

	for (int i = 0; i < nums2Size; i++)
	{
		while (!stackIsEmpty(s) && nums2[i] > stackTop(s))
		{
			int update = stackPop(s);
			int findIdx = findHash(h, update);
			if (-1 == findIdx)
			{
				continue;            
			}
			ret[findIdx] = nums2[i];
		}
		stackPush(s, nums2[i]);
	}

	releaseHash(h);
	stackFree(s);
	return ret;
}

