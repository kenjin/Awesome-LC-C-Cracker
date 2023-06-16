#define HASH_SIZE 5001
typedef struct hashT HASH;

struct hashInfo
{
	int fail;
	char str[51];
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
		obj->arr[x] = newInfo;
	}
	return obj;
}

void addHash(HASH *ht, char *key, char fail) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (*(ht->arr[index]->str) != 0) 
	{
		index++;
		index %= ht->size;
	}

	strncpy(ht->arr[index]->str, key, keyLen);
	ht->arr[index]->fail = fail;
}

int findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (*(ht->arr[index]->str) != 0) 
	{
		if (!strncasecmp(ht->arr[index]->str, key, keyLen))
		{
			return ht->arr[index]->fail;
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


bool isSubsequence(char * s, char * t)
{
	while (*t)
	{
		if (*s == *t)
		{
			s++;
			t++;
		} else
		{
			t++;
		}
	}

	return (*s == 0 ? true : false);
}

int numMatchingSubseq(char * S, char ** words, int wordsSize)
{
	int ret = 0;
	HASH *h = createHash(HASH_SIZE);
	for (int i = 0; i < wordsSize; i++)
	{
		int findRet = findHash(h, words[i]);
		if (-1 == findRet)
		{
			if (isSubsequence(words[i], S))
			{
				ret++;
				addHash(h, words[i], 0);
			} else
			{
				addHash(h, words[i], 1);
			}
		} else
		{
			ret = (findRet == 0 ? ret + 1 : ret);
		}
	}

	releaseHash(h);
	return ret;
}


