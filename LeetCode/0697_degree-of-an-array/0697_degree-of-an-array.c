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

typedef struct dataInfo
{
	int num;
	int head;   
	int tail;
	int freq;
}DATA;


int findShortestSubArray(int* nums, int numsSize)
{
	HASH *h = createHash(numsSize);

	DATA *d = malloc(sizeof(DATA)*numsSize);
	int dCtr = 0;
	for (int i = 0; i < numsSize; i++)
	{
		int findIdx = findHash(h, nums[i]);
		if (-1 == findIdx)
		{
			d[dCtr].num = nums[i];
			d[dCtr].head = i;
			d[dCtr].tail = i;
			d[dCtr].freq = 1;
			addHash(h, nums[i], dCtr);
			dCtr++;
		} else
		{
			d[findIdx].tail = i;
			d[findIdx].freq += 1;
		}
	}

	int maxFreq = INT_MIN;
	int ret = 1;
	for (int i = 0; i < dCtr; i++)
	{
		if (d[i].freq > maxFreq)
		{
			maxFreq = d[i].freq;
			ret = d[i].tail - d[i].head + 1;
		}
		if (d[i].freq == maxFreq)
		{
			int tmp = d[i].tail - d[i].head + 1;
			ret = tmp < ret ? tmp : ret;
		}
	}
	free(d);
	releaseHash(h);
	return ret;
}

