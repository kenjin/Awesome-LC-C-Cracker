typedef struct
{
	int size;
	int mod;
	int *arr;
} HASH;

int hash(HASH *obj, int key) 
{
	if (key < 0)
	{
		key *= (-1);
	}

	int r = key % obj->mod;
	return r < 0 ? r + obj->size : r;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->arr = calloc(size, sizeof(int));
	return obj;
}

void flushHash(HASH *ht)
{
	memset(ht->arr, 0, sizeof(int)*ht->size);
}

void addHash(HASH *ht, int *s, int key, int idx)
{
	int index = hash(ht, key);
	while (ht->arr[index] > 0) 
	{
		if (s[ht->arr[index] - 1] == key)
		{            
			return;
		}
		index++;
		index %= ht->size;
	}
	ht->arr[index] = idx;
}

bool findHash(HASH *ht, int *s, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index] > 0)
	{
		if (s[ht->arr[index] - 1] == target)
		{            
			return true;
		}
		index++;
		index %= ht->size;
	}
	return false;
}

void releaseHash(HASH *ht)
{
	free(ht->arr);
	free(ht);
}

bool splitArray(int* nums, int numsSize)
{  
	bool ret = false;
	HASH *h = createHash(numsSize+1);
	int *s = calloc(numsSize, sizeof(int));
	s[0] = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		s[i] = s[i-1] + nums[i];
	}

	for (int j = 3; j < numsSize-3; j++)
	{
		flushHash(h);
		int found = 0;
		for (int i = 1; i < j - 1; i++)
		{
			int sum_i_left  = s[i-1];
			int sum_i_right = s[j-1] - s[i];
			if (sum_i_left == sum_i_right)
			{
				found = 1;
				addHash(h, s, sum_i_left, i);
			}
		}

		if (!found)
		{
			continue;
		}
		for (int k = j + 1; k < numsSize - 1; k++)
		{
			int sum_k_left  = s[k-1] - s[j];
			int sum_k_right = s[numsSize-1] - s[k];
			if (sum_k_left == sum_k_right)
			{
				if (findHash(h, s, sum_k_left))
				{
					ret = true;
					goto out;
				}
			}
		}        
	}

out:
	releaseHash(h);
	free(s);    
	return ret;
}

