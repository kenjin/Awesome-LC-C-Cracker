
typedef struct dataInfo
{
	int freq;
	int len;
	char *str;
}DATA;

typedef struct hashT HASH;
struct hashInfo
{
	int idx;
	int len;
	char *str;       
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo **arr;
};

int hash(HASH *obj, char *str, int keyLen)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->size;
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
		newInfo->idx = -1;        
		obj->arr[x] = newInfo;
	}
	return obj;
}

void addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != -1) 
	{
		index++;
		index %= ht->size;
	}

	ht->arr[index]->str = calloc(keyLen+1, sizeof(char));
	ht->arr[index]->idx = idx;
	ht->arr[index]->len = keyLen;
	strncpy(ht->arr[index]->str, key, keyLen);
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->idx != -1) 
	{
		if (keyLen == ht->arr[index]->len &&
				!strcmp(ht->arr[index]->str, key))
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
		free(ht->arr[i]->str);
		free(ht->arr[i]);
	}
	free(ht->arr);
	free(ht);
}

int compare(const void *a, const void *b)
{
	DATA *n1 = (DATA *)a;
	DATA *n2 = (DATA *)b;

	if (n1->freq == n2->freq)
	{
		int idx1 = 0;
		int idx2 = 0;
		return strcmp(n2->str, n1->str);
	}
	return n1->freq - n2->freq;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize)
{
	HASH *h = createHash(wordsSize);
	DATA *tmp = malloc(sizeof(DATA)*wordsSize);
	int tmpCtr = 0;
	for (int i = 0; i < wordsSize; i++)
	{
		int findIdx = findHash(h, words[i]);
		if (-1 == findIdx)
		{
			addHash(h, words[i], tmpCtr);
			int tmpLen = strlen(words[i]);
			tmp[tmpCtr].freq = 1;
			tmp[tmpCtr].len = tmpLen;
			tmp[tmpCtr].str = calloc(tmpLen+1, sizeof(char));
			memcpy(tmp[tmpCtr].str, words[i], sizeof(char)*tmpLen);
			tmpCtr++;
		} else
		{
			tmp[findIdx].freq += 1;
		}
	}

	qsort(tmp, tmpCtr, sizeof(DATA), compare);

	char **ret = malloc(sizeof(char *)*k);
	int retCtr = 0;
	for (int x = 0; x < k; x++)
	{        
		ret[retCtr] = calloc(tmp[tmpCtr-1].len+1, sizeof(char));
		memcpy(ret[retCtr], tmp[tmpCtr-1].str, sizeof(char)*(tmp[tmpCtr-1].len));
		free(tmp[tmpCtr-1].str);
		retCtr++;
		tmpCtr--;
	}

	for (int x = 0; x < tmpCtr; x++)
	{
		free(tmp[x].str);
	}        
	free(tmp);
	releaseHash(h);

	*returnSize = retCtr;
	return ret;
}

