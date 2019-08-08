struct hashInfo
{
	int idx;
	int val;   
};

typedef struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
}HASH;

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

bool checkSubarraySum(int* nums, int numsSize, int k)
{
	bool ret = false;
	// corner case: k is negative
	k = (k < 0 ? k*-1 : k);
	// corner case: consecutive zero check
	for (int i = 1; i < numsSize; i++)
	{
		if (nums[i] == 0 && nums[i-1] == 0)
		{
			return true;
		}
	}
	// corner case: k is zero and no consecutive zero
	if (k == 0)
	{
		return false;
	}

	int minSize = (numsSize < k ? numsSize : k);
	int *modSet = malloc(sizeof(int)*minSize);
	int setCtr = 0;

	HASH *h = createHash(minSize);
	int rem = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] == 0)
		{
			continue;
		}

		rem = (rem + nums[i]) % k;
		if (i > 0 && rem == 0)
		{
			ret = true;
			break;
		}

		int findRet = findHash(h, rem);
		if (-1 == findRet)
		{
			modSet[setCtr] = i;
			addHash(h, rem, setCtr);
			setCtr++;
		} else
		{
			if (modSet[findRet] != -1 && (i - modSet[findRet]) > 1)
			{
				ret = true;
				break;
			}
			modSet[findRet] = i;   
		}
	}

	free(modSet);
	releaseHash(h);
	return ret;
}

