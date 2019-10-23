#define MIN(a, b) (a < b ? a : b)

typedef struct
{
	int *idx;
	int idxCtr;
} INDEX_INFO;

typedef struct
{
	int len;
	char *str;
	INDEX_INFO *iInfo;
} INFO;

typedef struct 
{
	int size;
	int mod;
	INFO *info;    
} WordDistance;


int hash(WordDistance *obj, char *str)
{
	size_t hash = 5381;
	while (*str)
	{
		hash = 33 * hash ^ (unsigned char) *str++;
	}
	return hash % obj->size;
}

WordDistance* createHash(int size)
{
	WordDistance *obj = malloc(sizeof(WordDistance));
	obj->size = size;
	obj->mod = size;
	obj->info = calloc(size, sizeof(INFO));
	return obj;
}

void addHash(WordDistance *ht, char *key, int addIdx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key);
	while (ht->info[index].iInfo != NULL) 
	{
		index++;
		index %= ht->size;
	}

	ht->info[index].len = keyLen;
	ht->info[index].str = calloc(keyLen+1, sizeof(char));
	strcpy(ht->info[index].str, key);

	INDEX_INFO *newIdxInfo = malloc(sizeof(INDEX_INFO));
	newIdxInfo->idx = malloc(sizeof(int)*ht->size);
	newIdxInfo->idx[0] = addIdx;
	newIdxInfo->idxCtr = 1;
	ht->info[index].iInfo = newIdxInfo;
}

// The third parameter addIdx should be zero or positive integer, we use -1 to mean 
// that no need to update key and addIdx
INDEX_INFO* findAndUpdateHash(WordDistance *ht, char *key, int addIdx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key);
	while (ht->info[index].iInfo != NULL)
	{
		if (!strncmp(ht->info[index].str, key, keyLen))
		{
			if (addIdx != -1)
			{
				ht->info[index].iInfo->idx[ht->info[index].iInfo->idxCtr] = addIdx;
				ht->info[index].iInfo->idxCtr += 1;
			}
			return ht->info[index].iInfo;
		}
		index++;
		index %= ht->size;
	}
	return NULL;
}

void releaseHash(WordDistance *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		if (ht->info[i].iInfo)
		{
			free(ht->info[i].iInfo->idx);
			free(ht->info[i].iInfo);
		}
		free(ht->info[i].str);
	}
	free(ht->info);
	free(ht);
}

WordDistance* wordDistanceCreate(char ** words, int wordsSize) 
{
	WordDistance *wd = createHash(wordsSize);
	for (int i = 0; i < wordsSize; i++)
	{
		INDEX_INFO *findData = findAndUpdateHash(wd, words[i], i);
		if (NULL == findData)
		{
			addHash(wd, words[i], i);
		}
	}

	return wd;
}

int findShortest(INDEX_INFO *find1, INDEX_INFO *find2) 
{
	int i = 0, j = 0, res = INT_MAX;
	while (i < find1->idxCtr && j < find2->idxCtr) 
	{
		int diff = abs(find1->idx[i] - find2->idx[j]);
		res = MIN(res, diff);

		if (find1->idx[i] < find2->idx[j])
		{
			i++;
		} else
		{
			j++;
		}
	}

	return res;
}

int wordDistanceShortest(WordDistance* obj, char * word1, char * word2) 
{
	INDEX_INFO *find1 = findAndUpdateHash(obj, word1, -1);
	INDEX_INFO *find2 = findAndUpdateHash(obj, word2, -1);

	return findShortest(find1, find2);
}

void wordDistanceFree(WordDistance* obj) 
{
	releaseHash(obj);    
}

/**
 * Your WordDistance struct will be instantiated and called as such:
 * WordDistance* obj = wordDistanceCreate(words, wordsSize);
 * int param_1 = wordDistanceShortest(obj, word1, word2);

 * wordDistanceFree(obj);
 */
