typedef struct hashT HASH;
struct hashInfo
{
	int ctr; // Use ctr to handle "k = 0" case, we wonder to update the same pair once
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
		struct hashInfo *newInfo = calloc(1, sizeof(struct hashInfo));
		obj->arr[x] = newInfo;
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
		}
		index++;
		index %= ht->size;
	}
	ht->arr[index]->val = key;
	ht->arr[index]->ctr = 1;
}

int findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index]->ctr != 0) 
	{
		if (ht->arr[index]->val == target) 
		{            
			ht->arr[index]->ctr += 1;
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

int findPairs(int* nums, int numsSize, int k)
{
	int ret = 0;
	HASH *h = createHash(numsSize+1);
	if (k < 0)
	{
		return 0;
	}

	for (int i = 0; i < numsSize; i++)
	{
		if (k == 0)
		{
			// we will increase ctr when we find the target,
			// so we can avoid to update duplicate pair.
			if (2 == findHash(h, nums[i]))
			{
				ret++;
			}
		} else
		{
			if (findHash(h, nums[i]))
			{
				continue;
			}

			ret = (findHash(h, nums[i]-k) ? ret + 1 : ret);
			ret = (findHash(h, nums[i]+k) ? ret + 1 : ret);
		}
		addHash(h, nums[i]);
	}

	releaseHash(h);
	return ret;
}

