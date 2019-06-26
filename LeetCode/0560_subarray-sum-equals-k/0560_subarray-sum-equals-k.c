typedef struct hashT HASH;

struct hashInfo
{
	int ctr;
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
		obj->arr[x] = calloc(1, sizeof(struct hashInfo));
	}
	return obj;
}

void addHash(HASH *ht, int key) 
{
	int index = hash(ht, key);
	while (ht->arr[index]->ctr != 0) 
	{
		if (ht->arr[index]->val == key)
		{            
			ht->arr[index]->ctr += 1;
			return;
		}
		index++;
		index %= ht->size;
	}
	ht->arr[index]->ctr = 1;
	ht->arr[index]->val = key;
}

int findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index]->ctr != 0) 
	{
		if (ht->arr[index]->val == target) 
		{
			return ht->arr[index]->ctr;
		}
		index++;
		index %= ht->size;
	}
	return 0;
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

int subarraySum(int* nums, int numsSize, int k)
{
	int ret = 0;    	
	HASH *h = createHash(numsSize*3);
	addHash(h, 0);    
	int preSum = 0;
	for (int x = 0; x < numsSize; x++)
	{
		preSum += nums[x];
		ret += findHash(h, preSum - k);
		addHash(h, preSum);
	}

	releaseHash(h);
	return ret;
}
