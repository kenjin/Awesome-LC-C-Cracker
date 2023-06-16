#define HASH_NOT_FOUND  (-2)
#define HASH_ORIGINAL_IDX  (-1)

typedef struct hashTable HASH;
typedef struct dataInfo
{
	int used;
	int idx;
	int sum;
} DATA;

struct hashTable
{
	int size;
	int mod;
	DATA *d;
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
	obj->d = calloc(size, sizeof(DATA));
	return obj;
}

void addHash(HASH *ht, int key, int idx) 
{
	int index = hash(ht, key);
	while (ht->d[index].used)
	{
		index++;
		index %= ht->size;
	}
	ht->d[index].idx = idx;
	ht->d[index].sum = key;
	ht->d[index].used = 1;
}

int findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->d[index].used) 
	{
		if (ht->d[index].sum == target)
		{
			return ht->d[index].idx;
		}
		index++;
		index %= ht->size;
	}
	return HASH_NOT_FOUND;
}

void releaseHash(HASH *ht)
{
	free(ht->d);
	free(ht);
}

int maxSubArrayLen(int* nums, int numsSize, int k)
{
	int ret = 0;
	int prefixSum = 0;
	HASH *h = createHash(numsSize+1);    
	// Add default prefix sum
	addHash(h, 0, HASH_ORIGINAL_IDX);
	for (int i = 0; i < numsSize; i++)
	{
		prefixSum += nums[i];
		// Find the prefix sum of subarray that has -k difference
		int findRet = findHash(h, prefixSum - k);      
		if (HASH_NOT_FOUND != findRet)
		{            
			int tmp = i - findRet;
			ret = ret > tmp ? ret : tmp;
		}
		// Update current prefix sum to hash table
		if (HASH_NOT_FOUND == findHash(h, prefixSum))
		{
			addHash(h, prefixSum, i);
		}
	}

	releaseHash(h);    
	return ret;
}

