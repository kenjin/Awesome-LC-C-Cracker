#define MALLOC_UNIT          (500)
#define PHRAS_COUNT         (100)

typedef struct hashT HASH;
typedef struct idxInfo IDXINFO;

struct idxInfo
{
	int ctr;
	int indice[PHRAS_COUNT];
};

struct hashInfo
{
	IDXINFO *iinfo; 
	int len;
	char str[200];  /* Reserve max size of concacted string */
};

struct hashT
{
	int size;
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
	obj->arr = malloc(sizeof(struct hashInfo *)*(size));
	for (int x = 0; x < size; x++)
	{
		obj->arr[x] = calloc(1, sizeof(struct hashInfo));
		obj->arr[x]->iinfo = calloc(1, sizeof(IDXINFO));
	}
	return obj;
}

void addHash(HASH *ht, char *key, int idx) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->iinfo->ctr != 0) 
	{
		if (ht->arr[index]->len == keyLen &&
				!strcmp(ht->arr[index]->str, key))
		{
			break;
		}
		index++;
		index %= ht->size;
	}

	ht->arr[index]->iinfo->indice[ht->arr[index]->iinfo->ctr] = idx;
	ht->arr[index]->iinfo->ctr += 1;    
	ht->arr[index]->len = keyLen;
	strcpy(ht->arr[index]->str, key);
}

IDXINFO* findHash(HASH *ht, char *key) 
{
	int keyLen = strlen(key);
	int index = hash(ht, key, keyLen);
	while (ht->arr[index]->iinfo->ctr != 0)
	{
		if (ht->arr[index]->len == keyLen &&
				!strcmp(ht->arr[index]->str, key))
		{
			return ht->arr[index]->iinfo;
		}
		index++;
		index %= ht->size;
	}
	return NULL;
}

void releaseHash(HASH *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		free(ht->arr[i]->iinfo);
		free(ht->arr[i]);        
	}
	free(ht->arr);
	free(ht);
}

int compare(const void *a, const void *b)
{
	char *str1 = *(char **)a;
	char *str2 = *(char **)b;

	return strcmp(str1, str2);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** beforeAndAfterPuzzles(char ** phrases, int phrasesSize, int* returnSize)
{
	char **ret = malloc(sizeof(char *)*MALLOC_UNIT);
	*returnSize = 0;

	HASH *h = createHash(phrasesSize+1);
	HASH *retH = createHash((phrasesSize*(phrasesSize-1))/2+1);
	for (int i = 0; i < phrasesSize; i++)
	{
		int len = strlen(phrases[i]);
		// Update the last word of the first phrase 
		for (int x = len-1; x >= 0; x--)
		{            
			if (x == 0 || phrases[i][x] == ' ')
			{
				char *tmp = (x == 0 ? phrases[i] : &(phrases[i][x+1]));
				addHash(h, tmp, i);                
				break;
			}
		}        
	}

	IDXINFO *findRet = NULL;
	char *concatStr = NULL;
	for (int i = 0; i < phrasesSize; i++)
	{
		int len = strlen(phrases[i]);                
		// Check the first word of the second phrase
		for (int x = 0; x < len; x++)
		{
			if (x == len-1 || phrases[i][x] == ' ')
			{
				findRet = NULL;
				concatStr = NULL;
				if (x == len-1)
				{
					findRet = findHash(h, phrases[i]);
				} else
				{
					phrases[i][x] = 0;
					findRet = findHash(h, phrases[i]);
					phrases[i][x] = ' ';
					concatStr = &(phrases[i][x+1]);    
				}

				if (findRet != NULL)
				{
					for (int k = 0; k < findRet->ctr; k++)
					{
						if (i == findRet->indice[k])
						{
							continue;
						}
						ret[*returnSize] = calloc(200, sizeof(char));

						if (x == len-1)
						{
							strcpy(ret[*returnSize], phrases[findRet->indice[k]]);
						} else
						{
							sprintf(ret[*returnSize], "%s %s", phrases[findRet->indice[k]], concatStr);
						}

						if (findHash(retH, ret[*returnSize]) != NULL)
						{
							free(ret[*returnSize]);
							continue;
						}
						addHash(retH, ret[*returnSize], -1);
						*returnSize += 1;
						if (*returnSize % MALLOC_UNIT == 0)
						{
							ret = realloc(ret, sizeof(char *)*(*returnSize+MALLOC_UNIT));
						}
					}
				}
			}            
		}
	}

	// Sorted lexicographically
	qsort(ret, *returnSize, sizeof(char *), compare);
	releaseHash(retH);
	releaseHash(h);
	return ret;
}

