typedef struct hashT HASH;

struct hashInfo
{
	int idx;
	int val;   
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

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
	obj->arr = malloc(sizeof(struct hashInfo)*(size));
	for (int x = 0; x < size; x++)
	{
		struct hashInfo *newInfo = malloc(sizeof(struct hashInfo));
		obj->arr[x] = newInfo;
		newInfo->idx = -1;
	}
	return obj;
}

void addHash(HASH *ht, int key, int idx) 
{
	int index = hash(ht, key);
	while (ht->arr[index]->idx != -1) 
	{
		index++;
		index %= ht->size;
	}
	ht->arr[index]->idx = idx;
	ht->arr[index]->val = key;
}

int findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index]->idx != -1) 
	{
		if (ht->arr[index]->val == target) 
		{
			return ht->arr[index]->idx;
		}
		index++;
		index %= ht->size;
	}
	return -1;
}

void releaseHash(HASH *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		free(ht->arr[i]);
	}
	free(ht->arr);
	free(ht);
}

int* twoSum(int* nums, int numsSize, int target, int *returnSize) 
{
	int *indices = NULL;
	*returnSize = 0;
	HASH *ht = createHash(numsSize);
	for (int i = 0; i < numsSize; i++) 
	{
		int complements = target - nums[i];
		int index = findHash(ht, complements);
		if (index >= 0) 
		{
			indices = (int *)malloc(sizeof(int) * 2);
			indices[0] = index;
			indices[1] = i;
			*returnSize = 2;
			break;
		}
		addHash(ht, nums[i], i);
	}

	releaseHash(ht);
	return indices;
}
